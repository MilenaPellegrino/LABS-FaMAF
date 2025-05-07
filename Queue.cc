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
// Elementos publicos, todo el sistema puede accederlos.
public:
    // Funciones que no termino de entender
    // Posiblemente usadas por omnet.
    Queue();
    virtual ~Queue();
// Elementos protegidos, propios y accedidos tambien por subclases.
protected:
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
            cMessage *pkt = (cMessage*) buffer.pop();
            // Envia paquete
            send(pkt, "out");
            // Calcula duracion de envio
            //serviceTime = pkt->getDuration();            
            /* 
            Ver que opcion preferimos, si la anterior o la sig, la diferencia
            esta en como calcular el serviceTime, si con la duracion del paquete
            o con lo definido en el .ini
            */
            serviceTime = par("serviceTime");
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

#endif /* QUEUE */