#ifndef NET
#define NET

#include <string.h>
#include <omnetpp.h>
#include <packet_m.h>

using namespace omnetpp;

class Net: public cSimpleModule {
private:

public:
    Net();
    virtual ~Net();
    struct RouteInfo {
        int bestInterface = -1;
        simtime_t lastDelay = SIMTIME_ZERO;
        int packetsSent = 0;
        int feedbacksReceived = 0;
    };
    std::map<std::pair<int, int>, RouteInfo> routingTable;
    std::set<std::pair<int, int>> testSent;
protected:
    virtual void initialize();
    virtual void finish();
    virtual void handleMessage(cMessage *msg);
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

void Net::handleMessage(cMessage *msg) {

    // All msg (events) on net are packets
    
    Packet *pkt = (Packet *) msg;
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
 
    if (type == 2) {//el paquete es un feedback
        if (dest == myIndex) {
            //llego a su destino
            std::pair<int, int> key = std::make_pair(myIndex, origin);
            int arrivedGate = pkt->getArrivalGate()->getIndex();
            simtime_t delay = simTime() - pkt->getCreationTime(); // Delay estimado
        
            // Si no había info, o la nueva es mejor, actualizamos
            if (routingTable.find(key) == routingTable.end() || delay < routingTable[key].lastDelay) {
                routingTable[key].bestInterface = arrivedGate;
                routingTable[key].lastDelay = delay;
            }
            delete pkt; // ya no se necesita

            } else {
                // reenviar el feedback hacia su origen
                int arrivedGate = pkt->getArrivalGate()->getIndex();
                // enviamos por el lado opuesto
                int returnIface;
                if (arrivedGate == 0){
                    returnIface = 1;
                }else{
                    returnIface = 0; 
                }
                send(pkt, "toLnk$o", returnIface);
            }
               

    }else if(type == 1){//el paquete es un test
        if (dest == myIndex) {
            // el test llega al destino
            // Creamos un paquete de feedback para retornar
            Packet *feedback = pkt->dup();
            feedback->setPacketType(2);
            //se lo mandamos de vuelta al origen
            feedback->setDestination(origin);
            feedback->setSource(myIndex);
        
            // Tomamos la interfaz por donde vino este test
            int arrivedGate = pkt->getArrivalGate()->getIndex();
            
            send(feedback, "toLnk$o", arrivedGate);
            // eliminamos el paquete de test que ya es inecesario
            delete pkt; 
        } else {
            // reenviamos el test en la misma dirección
            int arrivedGate = pkt->getArrivalGate()->getIndex();
            // enviamos por el lado opuesto
             int returnIface;
            if (arrivedGate == 0){
                returnIface = 1;
            }else{
                returnIface = 0; 
            }
            send(pkt, "toLnk$o", returnIface);
        }
    
    }else if(dest == myIndex){//el paquete es original y esta en el final
        send(msg, "toApp$o");
    }else if(origin == myIndex){//es el paquete original y esta al principio
        // Creamos una clave única para la tabla de ruteo: (origen, destino)
        std::pair<int, int> key = std::make_pair(origin, dest);
        // Verificamos si ya tenemos una ruta registrada
        if (routingTable.find(key) != routingTable.end()) {
            // Ruta conocida: reenviar por la mejor interfaz registrada
            int bestIface = routingTable[key].bestInterface;

            // por si el valor no es válido
            
            if (bestIface >= 0 && bestIface < gateSize("toLnk$o")) {
                send(msg, "toLnk$o", bestIface);
            } else {
            // Si por alguna razón el valor es inválido, reenviar por interfaz por defecto (0)
            send(msg, "toLnk$o", 0);
            }
        } else {
            // no hay ruta optima actualmente y estamos en el lugar de origen del paquete
            if (testSent.find(key) == testSent.end()){ //se hizo el primer test?
                //si no
                //Marcamos que se hizo el testeo
                testSent.insert(key);
                //creamos paquetes de testeo
                Packet *test1 = new Packet("testPacket1");
                Packet *test2 = new Packet("testPacket2");
                test1->setPacketType(1);
                test2->setPacketType(1);
                test1->setSource(myIndex);
                test2->setSource(myIndex);
                test1->setDestination(dest);
                test2->setDestination(dest);
                test1->setByteLength(128);
                test2->setByteLength(128);
                //lo enviamos por ambos lados
                send(test1, "toLnk$o", 0); // horario
                send(test2, "toLnk$o", 1); // antihorario
                //enviamos el original
                send(pkt, "toLnk$o", 0);
            }else{
                //si ya se hizo el test pero aun no se tiene ruta se envia por defecto
                send(msg, "toLnk$o", 0);
            }
        }
    }else{//es el paquete original y no esta al principio ni al final
        int arrivedGate = pkt->getArrivalGate()->getIndex();
        // enviamos por el lado opuesto 
        //(hay muchos de estos ya que al principio me salio la cosa al reves)
        int returnIface;
        if (arrivedGate == 0){
            returnIface = 1;
        }else{
            returnIface = 0; 
        }
        send(pkt, "toLnk$o", returnIface);
    }
}