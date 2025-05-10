#ifndef QUEUE
#define QUEUE

#include <string.h>
#include <omnetpp.h>

// La sig linea permite no escribir omnetpp en cada funcion de omnet
using namespace omnetpp;

// Clase Queue hereda de cSimpleModule definido en archivo .ned
class Queue: public cSimpleModule {
// Elementos privados, propios de cada instancia de Queue
private:
// Elementos publicos, todo el sistema puede accederlos.
public:
    // Funciones que no termino de entender
    // Posiblemente usadas por omnet.
    Queue();
    virtual ~Queue();
// Elementos protegidos, propios y accedidos tambien por subclases.
protected:
    // Cola donde guardar paquetes entrantes.
    cQueue buffer;
    // Donde se reciben mensajes (nombre confuso).
    cMessage *endServiceEvent;
    // Var para calcular tiempo de envio.
    simtime_t serviceTime;
    // Vector que cuenta paquetes encolados.
    cOutVector bufferSizeVector;
    // Vector que cuenta paquetes deshechados.
    cOutVector packetDropVector;
    // Metodo de valores iniciales.
    virtual void initialize();
    // Metodo de terminar programa.
    virtual void finish();
    // Metodo de manejo de mensajes.
    virtual void handleMessage(cMessage *msg);
};

// La sig. linea indica que se definira el comportamiento del modulo definido
// En el archivo .ned
Define_Module(Queue);

// No entiendo como afecta que el mensaje sea NULL
Queue::Queue() {
    endServiceEvent = NULL;
}

// Detiene el envio de un mensaje.
Queue::~Queue() {
    cancelAndDelete(endServiceEvent);
}

// Pone nombre al buffer y inicia la recepcion de mensajes.
void Queue::initialize() {
    buffer.setName("buffer");
    bufferSizeVector.setName("bufferSize");
    packetDropVector.setName("packetDrop");
    endServiceEvent = new cMessage("endService");
}

// Vacio por que?
void Queue::finish() {
}

// Funcion principal.
void Queue::handleMessage(cMessage *msg) {
    if (msg == endServiceEvent) {
    // Si hay via libre para enviar paquetes
        if (!buffer.isEmpty()) {
        // Si hay elementos en el buffer
            // Quita paquete del buffer
            cPacket *pkt = (cPacket*) buffer.pop();
            // Envia paquete
            send(pkt, "out");
            // Calcula duracion de envio
            serviceTime = pkt->getDuration();            
            /* 
            Ver que opcion preferimos, si la anterior o la sig, la diferencia
            esta en como calcular el serviceTime, si con la duracion del paquete
            o con lo definido en el .ini
            */
            //serviceTime = par("serviceTime");
            // Cuando pasen serviceTime secs autoenvia mensaje de via libre.
            // Es decir cuando pasen serviceTime secs se ejecuta 
            // handleMessage(endServiceTime)
            scheduleAt(simTime() + serviceTime, endServiceEvent);
        }
    } else { 
    // Si no hay via libre para enviar paquetes
        if(buffer.getLength() > par("bufferSize").doubleValue()) {
        // Si la longitud de la cola es mayor que lo definido en .ini
            // Tiramos el paquete
            delete msg;
            // Muestra mensaje en interfaz grafica de paquete tirado.
            this->bubble("packet dropped");
            // Se cuenta el paquete tirado.
            packetDropVector.record(1);
        } else {
        // Si hay espacio en la cola
            // Encolar el paquete
            buffer.insert(msg);
            // Se actualiza tamaño de cola actual.
            bufferSizeVector.record(buffer.getLength());
            if (!endServiceEvent->isScheduled()) {
            // Si el mensaje ya fue enviado.
                // Se envia mensaje de via libre.
                scheduleAt(simTime(), endServiceEvent);
            }
        }
    }
}

class TransportTx : public Queue {
private:
    double timeModifier;
protected:
    void initialize();
    // Metodo de terminar programa.
    void finish();
    // Metodo de manejo de mensajes.
    void handleMessage(cMessage *msg);
};

// La sig. linea indica que se definira el comportamiento del modulo definido
// En el archivo .ned
Define_Module(TransportTx);

// Pone nombre al buffer y inicia la recepcion de mensajes.
void TransportTx::initialize() {
    timeModifier = 0;
    buffer.setName("buffer");
    bufferSizeVector.setName("bufferSize");
    packetDropVector.setName("packetDrop");
    endServiceEvent = new cMessage("endService");
}

// Vacio por que?
void TransportTx::finish() {
}

// Funcion principal.
void TransportTx::handleMessage(cMessage *msg) {
    switch(msg->getKind()) {
    case 0:
        if (msg == endServiceEvent) {
        // Si hay via libre para enviar paquetes
            if (!buffer.isEmpty()) {
            // Si hay elementos en el buffer
                // Quita paquete del buffer
                cPacket *pkt = (cPacket*) buffer.pop();
                pkt->addPar("traTxTime") = const_simtime_t();
                // Envia paquete
                send(pkt, "toOut$o");
                // Calcula duracion de envio
                if (timeModifier == 0) {
                    serviceTime = pkt->getDuration();
                } else {
                    serviceTime = pkt->getDuration() * timeModifier;
                }           
                /* 
                Ver que opcion preferimos, si la anterior o la sig, la diferencia
                esta en como calcular el serviceTime, si con la duracion del paquete
                o con lo definido en el .ini
                */
                //serviceTime = par("serviceTime");
                // Cuando pasen serviceTime secs autoenvia mensaje de via libre.
                // Es decir cuando pasen serviceTime secs se ejecuta 
                // handleMessage(endServiceTime)
                scheduleAt(simTime() + serviceTime, endServiceEvent);
            }
        } else { 
        // Si no hay via libre para enviar paquetes
            if(buffer.getLength() > par("bufferSize").intValue()) {
            // Si la longitud de la cola es mayor que lo definido en .ini
                // Tiramos el paquete
                delete msg;
                // Muestra mensaje en interfaz grafica de paquete tirado.
                this->bubble("packet dropped");
                // Se cuenta el paquete tirado.
                packetDropVector.record(1);
            } else {
            // Si hay espacio en la cola
                // Encolar el paquete
                buffer.insert(msg);
                // Se actualiza tamaño de cola actual.
                bufferSizeVector.record(buffer.getLength());
                if (!endServiceEvent->isScheduled()) {
                // Si el mensaje ya fue enviado.
                    // Se envia mensaje de via libre.
                    scheduleAt(simTime(), endServiceEvent);
                }
            }
        }
    case 1:
        cPacket *pkt = (cPacket*) msg;
        if (pkt->hasPar("delayAlert")) {
            timeModifier = pkt->par("delayAlert").doubleValue();
        }
    }
}

class TransportRx : public Queue {
private: 
    double newDelayMean;
    cQueue delays;
    void countMean();
protected:
    void initialize();
    // Metodo de terminar programa.
    void finish();
    // Metodo de manejo de mensajes.
    void handleMessage(cMessage *msg);
};

// La sig. linea indica que se definira el comportamiento del modulo definido
// En el archivo .ned
Define_Module(TransportRx);

// Pone nombre al buffer y inicia la recepcion de mensajes.
void TransportRx::initialize() {
    buffer.setName("buffer");
    delays.setName("delays");
    bufferSizeVector.setName("bufferSize");
    packetDropVector.setName("packetDrop");
    endServiceEvent = new cMessage("endService");
}

// Vacio por que?
void TransportRx::finish() {
}

// Funcion principal.
void TransportRx::handleMessage(cMessage *msg) {
    if (msg == endServiceEvent) {
    // Si hay via libre para enviar paquetes
        if (!buffer.isEmpty()) {
        // Si hay elementos en el buffer
            // Quita paquete del buffer
            cPacket *pkt = (cPacket*) buffer.pop();            
            // Envia paquete
            send(pkt, "toOut$o");
            // Calcula duracion de envio
            serviceTime = pkt->getDuration();            
            // Cuando pasen serviceTime secs autoenvia mensaje de via libre.
            // Es decir cuando pasen serviceTime secs se ejecuta 
            // handleMessage(endServiceTime)
            scheduleAt(simTime() + serviceTime, endServiceEvent);
        
        }
    } else { 
    // Si no hay via libre para enviar paquetes
        if(buffer.getLength() > par("bufferSize").intValue()) {
        // Si la longitud de la cola es mayor que lo definido en .ini
            // Tiramos el paquete
            delete msg;
            // Muestra mensaje en interfaz grafica de paquete tirado.
            this->bubble("packet dropped");
            // Se cuenta el paquete tirado.
            packetDropVector.record(1);
        } else {
        // Si hay espacio en la cola
            cPacket *pkt = (cPacket*) msg;
            double aux, delay = pkt->par("traTxTime");
            // Encolar el paquete
            buffer.insert(msg);
            delay = const_simtime_t() - delay;
            // VERCOMO MIERDA GUARDAR EN LA COLA
            // CONSIDERAR CAMBIAR CQUEUE POR OTRA MIERDA
            if (delays.getLength() < 10) {
                delays.insert(delayObj);
            } else {
                delays.pop();
                delays.insert(delayObj);
            }
            aux = newDelayMean;
            countMean();
            if (aux!=0) {
                if (aux + aux*0.25 <= newDelayMean) {
                    cPacket *appPkt = new cPacket("app_packet");
                    appPkt->setKind(1);
                    appPkt->par("delayAlert") = 0.25;
                    send(appPkt, "toApp");
                } else if (aux - aux*0.25 >= newDelayMean) {
                    cPacket *appPkt = new cPacket("app_packet");
                    appPkt->setKind(1);
                    appPkt->par("delayAlert") = -0.25;
                    send(appPkt, "toApp");
                } else {
                    cPacket *appPkt = new cPacket("app_packet");
                    appPkt->setKind(1);
                    appPkt->par("delayAlert") = 0;
                    send(appPkt, "toApp");
                }
            }
            // Se actualiza tamaño de cola actual.
            bufferSizeVector.record(buffer.getLength());
            if (!endServiceEvent->isScheduled()) {
            // Si el mensaje ya fue enviado.
                // Se envia mensaje de via libre.
                scheduleAt(simTime(), endServiceEvent);
            }
        }
    }
}

void TransportRx::countMean() {
    cQueue *aux = delays.dup();
    double iaux, length, sum = 0;
    length = aux->getLength();
    while (!aux->isEmpty()) {
        iaux = ((cValue*)aux->pop())->doubleValue();
        sum += iaux;
    }
    newDelayMean = sum / length;
    aux->~cQueue();
}
    
#endif /* QUEUE */