#ifndef NET
#define NET

//Los tipos de paquetes
const int TEST = 1;
const int FEEDBACK = 2;

//Los sentidos de envío
const int HORARIA = 0;
const int ANTIHORARIA = 1;

//Este es la X cantidad de paquetes que se envían hasta que se vuelve a reevaluar la ruta óptima
const int RESET_TESTING = 30;

#include <string.h>
#include <omnetpp.h>
#include <packet_m.h>

using namespace omnetpp;
using namespace std;

class Net: public cSimpleModule {
private:
    int sendedPackage = 0;
    int currentInterface = HORARIA; //En principio empieza a enviar en sentido horario
    map<int, bool> arrivalPackage; //Dado un origin nos devuelve si ya llego el primer paquete de testeo
    bool sendPackage = false; //Inicializamos en false, porque el primero que va a testear las rutas es firstTest
    bool firstTest = true; //Tiene que hacer el primer test

    //Vectores para analisis
    //CARGA
    cOutVector chargeVector;
    //PAQUETES TEST GENERADOS
    cOutVector testGenerated;
    //PAQUETES FEEDBACK GENERADOS
    cOutVector feedBackGenerated;
public:
    Net();
    virtual ~Net();
protected:
    virtual void initialize();
    virtual void finish();
    virtual void handleMessage(cMessage *msg); //Manejo de mensajes
    virtual void routing(cMessage *msg); //Metodo encargado de mandar los testeos de rutas.
    virtual void crearFeedback(cMessage *msg); //Encargado de mandar los feedBack
    virtual int gateOpuesto(cMessage *msg); //Dado un paquete/mensaje, devuelve el gate opuesto por el que llego ese paquete
};


Define_Module(Net);

#endif /* NET */

Net::Net() {
}

Net::~Net() {
}

void Net::initialize() {
    chargeVector.setName("charge");
    testGenerated.setName("tests");
    feedBackGenerated.setName("feedBacks");
}

void Net::finish() {
    recordScalar("charge", chargeVector.getValuesReceived());
}

void Net::routing(cMessage *msg){
    Packet *pkt = (Packet *) msg;

    //Creamos paquetes de testeo
    Packet *test0 = new Packet("testPacket0", this->getParentModule()->getIndex());
    Packet *test1 = new Packet("testPacket1", this->getParentModule()->getIndex());

    //Seteamos los tipos
    test0->setPacketType(TEST);
    test1->setPacketType(TEST);

    //Seteamos el origen
    test0->setSource(this->getParentModule()->getIndex());
    test1->setSource(this->getParentModule()->getIndex());

    //Seteamos el destino
    test0->setDestination(pkt->getDestination());
    test1->setDestination(pkt->getDestination());

    //Seteamos el largo
    test0->setByteLength((par("packetByteSizeTyF")));
    test1->setByteLength((par("packetByteSizeTyF")));

    //IMPORTANTE: ESTE VECTOR CUENTA LA CANTIDAD DE EVALUACIONES DE RUTA
    //CANTIDAD DE PAQUETES TEST = 2 * ESTE VECTOR
    testGenerated.record(1);
    
    // Enviamos los paquetes de testeo 
    send(test0, "toLnk$o", 0); // horario
    send(test1, "toLnk$o", 1); // antihorario
}

void Net::crearFeedback(cMessage *msg){
    Packet *pkt = (Packet *) msg;

    //Creamos paquete de feedback
    Packet *feedback = new Packet("feedback", this->getParentModule()->getIndex());

    //Seteamos el tipo
    feedback->setPacketType(FEEDBACK);

    //El origin del feedback es el destino del paquete testeo
    feedback->setSource(pkt->getDestination());

    //El destino del feedback es el origen del paquete de testeo
    feedback->setDestination(pkt->getSource());

    //El mismo tamaño que el paquete de testeo
    feedback->setByteLength(pkt->getByteLength());

    feedBackGenerated.record(1);
    
    //Enviamos el paquete feedback por la ruta que llego el primer paquete test
    send(feedback, "toLnk$o", pkt->getArrivalGate()->getIndex());
}

int Net::gateOpuesto(cMessage *msg){
    Packet *pkt = (Packet *) msg;
    //El index del Gate por el que llego
    int arrivedGate = pkt->getArrivalGate()->getIndex();

    //Nos interesa retornar el gate contrario
    //-----------------Al tratarse de interfaz booleana, podría negarse, pero entendemos que es menos expresivo. (Se entiende menos)
    int interfazOpuesta;

    if(arrivedGate == HORARIA){
        interfazOpuesta = ANTIHORARIA;
    }else{
        interfazOpuesta = HORARIA;
    }

    return interfazOpuesta;
}

void Net::handleMessage(cMessage *msg) {
    //Casteo el mensaje a Packet
    Packet *pkt = (Packet *) msg;
    chargeVector.record(chargeVector.getValuesReceived()+1);
    //Nodo actual
    int myIndex = this->getParentModule()->getIndex();
    //Destino
    int dest = pkt->getDestination();
    //Origen
    int origin = pkt->getSource();
    //Tipo de paquete
    int type = pkt->getPacketType();

    if (type == FEEDBACK) { //TIPO DE PAQUETE FEEDBACK
        if (dest != myIndex){ //Si no llego a destinio, sigue el mismo sentido
            send(pkt, "toLnk$o", gateOpuesto(msg));
        }
        //-----------------------------REVISAR SI ES MÁS EXPRESIVO ASÍ O CON ELSE (pero es equivalente).
        if (dest == myIndex) { //Llego a su destino
            currentInterface = pkt->getArrivalGate()->getIndex(); //Actualizo la ruta óptima ------------REVISAR (explicar en llamada)
            delete pkt; //Borramos el paquete
        }
    } else if(type == TEST){ //TIPO DE PAQUETE TEST
        if(dest != myIndex){ //Si no llego a destino, sigue el mismo sentido
            send(pkt, "toLnk$o", gateOpuesto(msg));
        }
        //-----------------------------REVISAR SI ES MÁS EXPRESIVO ASÍ O CON ELSE (pero es equivalente).
        if(dest == myIndex){ //Si el test llego a destino
            auto it = arrivalPackage.find(origin); //arrivalPackage devuelve un iterador (consultar)
            if(it == arrivalPackage.end() || !(it->second)){ //Si no existe en el map o si es false
                arrivalPackage[origin] = true; //Lo creamos o seteamos en true (SI LLEGO PAQUETE TEST)
                crearFeedback(msg); //Creo y envio feedBack
            } else {
                arrivalPackage[origin] = false; //Si ya había llegado un test, seteo el false para que el próximo test si lo tenga en cuenta. NO ES TRIVIAL
            }
            delete pkt; //Lo borro
        }

    }else{  // El paquete es "normal" o de dato

        if(dest == myIndex){ //Esta en el destino
            send(pkt, "toApp$o"); //Lo mando a APP
        } 
        
        else if (origin == myIndex){ //Esta al principio (lo acabo de recibir de APP)
            if (firstTest) { //Me fijo si es el primer test que tengo que hacer
                routing(msg); //Mando el primer test
                firstTest = false; //Lo seteo en false por el resto de la simulación

                //Para evitar la sincronización masiva
                int sendedPackage = static_cast<int>((static_cast<double>(this->getParentModule()->getIndex() % 10) / 10.0) * RESET_TESTING); //Todos los nodos van a arrancar con una cantidad distinta de paquetes enviados
            }
            if(sendPackage){ //Me fijo si toca enviar paquetes TEST.
                routing(msg); //Envio los TEST.
                sendedPackage = 0; //Reseteo el counter de paquetes enviados.
            } 
            sendedPackage++; //Pase lo que pase, incremento en contador de paquetes enviados (incluyendo a los TEST).
            sendPackage = sendedPackage > RESET_TESTING; //Me fijo si ya alcanzamos los paquetes necesarios para reevaluar con TEST.
            //Tomo los jumps de ese paquete
            long jumps = msg->par("Jumps").longValue();
            //Lo incremento en 1
            jumps++;
            //Lo vuelvo a settear
            msg->par("Jumps").setLongValue(jumps);
            send(pkt, "toLnk$o", currentInterface); //Envio el paquete original a destino
        }
        
        else {  //Esta en un nodo intermedio
            //Tomo los jumps de ese paquete
            long jumps = msg->par("Jumps").longValue();
            //Lo incremento en 1
            jumps++;
            //Lo vuelvo a settear
            msg->par("Jumps").setLongValue(jumps);
            send(pkt, "toLnk$o",   gateOpuesto(msg)); //Lo envio por el gate opuesto al recibido
        }
    }
}   
