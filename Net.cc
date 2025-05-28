#ifndef NET
#define NET

const int TEST = 1;
const int FEEDBACK = 2;

const int HORARIA = 0;
const int ANTIHORARIA = 1;

#include <string.h>
#include <omnetpp.h>
#include <packet_m.h>

using namespace omnetpp;
using namespace std;

class Net: public cSimpleModule {
private:
    int currentInterface = HORARIA;
    map<int, bool> arrivalPackage;  // Dado un origin nos devuelve si ya llego el primer paquete de testeo
    bool sendPackage = true;
    int sendedPackage = 0;
public:
    Net();
    virtual ~Net();
protected:
    virtual void initialize();
    virtual void finish();
    virtual void handleMessage(cMessage *msg);
    virtual void routing(cMessage *msg);
    virtual void crearFeedback(cMessage *msg);
    virtual int gateOpuesto(cMessage *msg);
};


Define_Module(Net);

#endif /* NET */

Net::Net() {
}

Net::~Net() {
}

void Net::initialize() {
    
}

void Net::finish() {
}

void Net::routing(cMessage *msg){
    Packet *pkt = (Packet *) msg;

    // creamos paquetes de testeo
    Packet *test0 = new Packet("testPacket0", this->getParentModule()->getIndex());
    Packet *test1 = new Packet("testPacket1", this->getParentModule()->getIndex());

    test0->setPacketType(TEST);
    test1->setPacketType(TEST);

    test0->setSource(this->getParentModule()->getIndex());
    test1->setSource(this->getParentModule()->getIndex());

    test0->setDestination(pkt->getDestination());
    test1->setDestination(pkt->getDestination());

    test0->setByteLength(pkt->getByteLength());
    test1->setByteLength(pkt->getByteLength());

    
    // Enviamos los paquetes de testeo 
    send(test0, "toLnk$o", 0); // horario
    send(test1, "toLnk$o", 1); // antihorario
}

void Net::crearFeedback(cMessage *msg){

    Packet *pkt = (Packet *) msg;

    // creamos paquetes de feedback
    Packet *feedback = new Packet("feedback", this->getParentModule()->getIndex());

    feedback->setPacketType(FEEDBACK);

    // El origin del feedback es el destino del paquete testeo
    feedback->setSource(pkt->getDestination());

    // El destino del feedback es el origen del paquete de testeo
    feedback->setDestination(pkt->getSource());

    feedback->setByteLength(pkt->getByteLength());
    
    // Enviamos los paquetes de testeo por la ruta optima elegida
    send(feedback, "toLnk$o", pkt->getArrivalGate()->getIndex());
}

int Net::gateOpuesto(cMessage *msg){
    Packet *pkt = (Packet *) msg;
    int arrivedGate = pkt->getArrivalGate()->getIndex();
    // enviamos por el lado opuesto
    int interfazOpuesta;
    if(arrivedGate == HORARIA){
        interfazOpuesta = ANTIHORARIA;
    }else{
        interfazOpuesta = HORARIA;
    }
    return interfazOpuesta;
}

void Net::handleMessage(cMessage *msg) {
    // All msg (events) on net are packets
    Packet *pkt = (Packet *) msg;

    cGate * arrivalGate = pkt->getArrivalGate();
    if(arrivalGate != nullptr){
        const char * gateName = arrivalGate->getName();
        if(strcmp(gateName, "toApp$i") == 0){
            if(sendPackage){
                routing(msg);
                sendPackage = false;
                sendedPackage = 0;
            } 
            sendedPackage++;
            sendPackage = sendedPackage > 15;
        }

    }

    //total de nodos
    int numHosts = getParentModule()->getVectorSize();
    //nodo actual
    int myIndex = this->getParentModule()->getIndex();
    //destino
    int dest = pkt->getDestination();
    //origen
    int origin = pkt->getSource();

    //tipo de paquete
    int type = pkt->getPacketType();

    if (type == FEEDBACK) {
        if (dest == myIndex) {
            // Llego a su destino
            currentInterface = pkt->getArrivalGate()->getIndex();
            delete pkt; // ya no se necesita
        } else {  // No llego a destino 
            send(pkt, "toLnk$o",   gateOpuesto(msg));
        }          
    } else if(type == TEST){
        // Si el test no llego a destino lo seguimos mandando por esa ruta
        if(dest!= myIndex){send(pkt, "toLnk$o", gateOpuesto(msg));}

        // Si el test llego a destino
        if(dest==myIndex){
            auto it = arrivalPackage.find(origin);
            if(it == arrivalPackage.end() || !(it->second)){
                arrivalPackage[origin] = true;
                currentInterface = gateOpuesto(msg);
                crearFeedback(msg);
            } else{
                arrivalPackage[origin] = false;
            }
            
            delete pkt;
        }

    }else{  // El paquete es "normal" 
        if(dest == myIndex){ // Esta en el destino
            send(pkt, "toApp$o");
        } else if (origin == myIndex){  // Esta al principio 
            send(pkt, "toLnk$o", currentInterface);
        } else {  // Esta en un nodo intermedio 
            send(pkt, "toLnk$o",   gateOpuesto(msg));
        }
    }

}   
    

    