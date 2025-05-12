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
    int ignore;
    simtime_t timeModifier, prevTimeModifier, scheduledTime;
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
    prevTimeModifier = 0;
    serviceTime = 0;
    scheduledTime = 0;
    ignore = 10;
    WATCH(timeModifier);
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
    switch(((cPacket *)msg)->getKind()) {
    case 0:
        this->bubble("Caso 0");
        if (msg == endServiceEvent) {
        // Si hay via libre para enviar paquetes
            if (!buffer.isEmpty()) {
            // Si hay elementos en el buffer
                // Quita paquete del buffer
                cPacket *pkt = (cPacket*) buffer.pop();
                simtime_t aux_st;
                // Envia paquete
                pkt->addPar("traTxTime") = simTime().dbl();
                send(pkt, "toOut$o");
                // Calcula duracion de envio         
                if (serviceTime == 0) {
                    serviceTime = pkt->getDuration();
                }
                aux_st = pkt->getDuration();
                if (serviceTime < aux_st) {
                    serviceTime = aux_st;
                }
                // Cuando pasen serviceTime secs autoenvia mensaje de via libre.
                // Es decir cuando pasen serviceTime secs se ejecuta 
                // handleMessage(endServiceTime)
                scheduledTime = simTime() + serviceTime;
                scheduleAt(scheduledTime, endServiceEvent);
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
                if (simTime() >= scheduledTime) {
                // Si el mensaje ya fue enviado.
                    // Se envia mensaje de via libre.
                    scheduleAt(simTime(), endServiceEvent);
                }
            }
        }
        break;
    case 1:
        this->bubble("Caso 1");
        if (ignore >= 10) {
            cPacket *pkt = (cPacket*) msg;
            timeModifier += pkt->par("delayAlert").doubleValue();
            if (timeModifier != prevTimeModifier) {
                serviceTime += serviceTime*timeModifier.dbl();
            }
            prevTimeModifier = timeModifier;
            ignore = 0;
        } else {
            ignore++;
        }
        delete msg;
        break;
    }
}

class TransportRx : public Queue {
private:
    simtime_t avgDelay, prevPktTime, aux, delay;
    cQueue delays;
    void countAvg();
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
    avgDelay = 0;
    prevPktTime = 0;
    WATCH(avgDelay);
    WATCH(aux);
    WATCH(delay);
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
            cPacket *del = new cPacket("del_packet"), *pkt = (cPacket*) msg;
            simtime_t pktTime;
            pktTime = simTime();
            // Encolar el paquete
            buffer.insert(msg);
            delay = pktTime - pkt->par("traTxTime").doubleValue();
            del->addPar("delay") = delay.dbl();
            if (delays.getLength() < 5) {
                delays.insert(del);
            } else {
                delays.pop();
                delays.insert(del);
            }
            if (delay != 0 && avgDelay != 0) {
                aux = (delay - avgDelay)/avgDelay;

                if (aux > par("errPercent") || 
                    aux < -par("errPercent").doubleValue()) {
                    cPacket *appPkt = new cPacket("app_packet");
                    appPkt->setKind(1);
                    if (aux > 0) {
                        appPkt->addPar("delayAlert") = par("errPercent").doubleValue();
                        appPkt->addPar("campus") = "aux > 0";
                    } else {
                        appPkt->addPar("delayAlert") = -par("errPercent").doubleValue();
                        appPkt->addPar("campus") = "aux < 0";
                    }
                    send(appPkt, "toApp");
                } else if (prevPktTime != 0){
                    if (prevPktTime+(delay*(1+par("errPercent").doubleValue())) <= pktTime) {
                        cPacket *appPkt = new cPacket("app_packet");
                        appPkt->setKind(1);
                        appPkt->addPar("delayAlert") = -par("errPercent").doubleValue();
                        appPkt->addPar("campus") = "outro";
                        send(appPkt, "toApp");
                    }
                }
            }
            countAvg();
            prevPktTime = pktTime;
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

void TransportRx::countAvg() {
    cQueue *aux = delays.dup();
    cPacket *del_pkt;
    simtime_t iaux, sum1 = 0;
    int length;
    length = 0;
    while (!aux->isEmpty()) {
        del_pkt = (cPacket*) aux->pop();
        if (del_pkt->hasPar("delay")) {
            iaux = del_pkt->par("delay").doubleValue();
            length++;

        } else {
            iaux = 0;
        }
        sum1 += iaux;
    }
    avgDelay = sum1 / length;
    aux->~cQueue();
}
    
#endif /* QUEUE */