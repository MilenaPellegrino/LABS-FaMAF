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
    // Intervalos de paquetes a ignorar desde la app
    int ignore;
    // timeModifier es un porcentaje obtenido desde la app
    // scheduledTime se encarga de saber cuando se envia el ultimo paq mandado
    simtime_t timeModifier, scheduledTime;
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
    // Valores iniciales
    timeModifier = 0;
    // A mayor serviceTime menos envio de paquetes
    // A menor serviceTime mas envio de paquetes
    serviceTime = 0;
    scheduledTime = 0;
    ignore = par("ignore").intValue();
    // WATCH sirve para ver valores en tiempos de ejecucion
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
    // Analisis por casos sobre el tipo de mensaje recibido
    switch(((cPacket *)msg)->getKind()) {
    case 0:
    // Mensaje para destino.
        if (msg == endServiceEvent) {
        // Si hay via libre para enviar paquetes
            if (!buffer.isEmpty()) {
            // Si hay elementos en el buffer
                // Quita paquete del buffer
                cPacket *pkt = (cPacket*) buffer.pop();
                simtime_t aux_st;
                // Guardo tiempo de salida del paquete desde NodeTx en paquete
                pkt->addPar("traTxTime") = simTime().dbl();
                // Envia paquete
                send(pkt, "toOut$o");
                // Calcula duracion de envio en caso inicial.
                if (serviceTime == 0) {
                    serviceTime = pkt->getDuration();
                }
                // Revisa si el serviceTime es menor que el tiempo de envio.
                aux_st = pkt->getDuration();
                if (serviceTime < aux_st) {
                    serviceTime = aux_st;
                }
                // Cuando pasen serviceTime secs autoenvia mensaje de via libre.
                // Es decir cuando pasen serviceTime secs se ejecuta 
                // handleMessage(endServiceTime)
                // Guarda el tiempo en el que se enviara el paquete.
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
    // Si el paquete viene desde la App.
        this->bubble("Caso 1");
        // El sig if, sirve para rafaga de paquetes
        // hasta estabilizar el promedio en el TransportTx
        if (ignore == par("ignore").intValue()) {
        // Si no debemos ignorar el paquete
            //Guardamos el paquete.
            cPacket *pkt = (cPacket*) msg;
            // Le agregamos al timeModifier el valor de porcentaje solicitado.
            timeModifier += pkt->par("delayAlert").doubleValue();
            // Se modifica el serviceTime con respecto al porcentaje que
            // debe aumentar o bajar
            serviceTime += serviceTime*timeModifier.dbl();
            // Se setea el ignore en 0 para ignorar los sig. paquetes
            timeModifier = 0;
            ignore = 0;
        } else {
        // Si debemos ignorar el paquete
            // Se suma 1 a ignore
            ignore++;
        }
        // Borramos mensaje recibido.
        delete msg;
        break;
    }
}

class TransportRx : public Queue {
private:
    // avgDelay sigue el promedio de los delays
    // pktTime registra el momento en que llega el paq. actual.
    // prevPkttime sirve para registrar en que momento llego el paq. anterior
    // delay se utiliza para registrar el delay actual
    // aux se utiliza para calcular el porcentaje de diferencia entre 
    // el avgDelay con el delay actual
    simtime_t avgDelay, prevPktTime, pktTime, aux, delay;
    // Cola que guarda los ultimos delays
    cQueue delays;
    // Funcion que calcula y modifica avgDelay para almacenar 
    // el promedio de la cola delays
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
    // Valores inicializados en 0
    avgDelay = 0;
    prevPktTime = 0;
    // Funciones para ver valores en tiempo de ejecucion
    WATCH(avgDelay);
    WATCH(aux);
    WATCH(delay);
    // Funciones de inicio de colas y vectores.
    buffer.setName("buffer");
    delays.setName("delays");
    bufferSizeVector.setName("bufferSize");
    packetDropVector.setName("packetDrop");
    // Inicio de manejo de mensajes con sig. linea
    endServiceEvent = new cMessage("endService");
}

// Vacio por que?
void TransportRx::finish() {
    delays.clear();
    delays.~cQueue();
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
            // Se registra el tiempo de llegada del paquete.
            pktTime = simTime();
            // Encolar el paquete
            buffer.insert(msg);

            // Se crea un paquete para guardar en cola delays.
            cPacket *auxPkt, *del = new cPacket("del_packet"), *pkt = (cPacket*) msg;
            // Se calcula el delay del paquete recibido
            delay = pktTime - pkt->par("traTxTime").doubleValue();
            // Se guarda el delay en el paquete que se guardara en delays.
            del->addPar("delay") = delay.dbl();
            //El sig if se encarga de que la cola nunca tenga mas elementos 
            //de los solicitados
            if (delays.getLength() >= par("delaySize").intValue()) {
            // Si la cola llego al limite
                //Elimino primer elemento
                auxPkt = (cPacket *) delays.pop();
                delete auxPkt;    
            }
            // Guardo el paquete en delays.
            delays.insert(del);
            if (buffer.getLength() >= 0.5*par("bufferSize").intValue()) {
            // Si el buffer esta al 50% de su caṕacidad o mayor
                aux = buffer.getLength();
                // Creamos paquete para enviar en la App
                cPacket *appPkt = new cPacket("app_packet");
                // Se setea su tipo en 1
                appPkt->setKind(1);
                // Solicita aumentar serviceTime
                if (aux<0.75*par("bufferSize").intValue()) {
                    appPkt->addPar("delayAlert") = 
                    par("fixPercent").doubleValue();
                } else {
                    appPkt->addPar("delayAlert") = 
                    2*par("fixPercent").doubleValue();
                }
                //appPkt->addPar("delayAlert") = aux.dbl();
                // Campo de debuggeo
                appPkt->addPar("campus") = "length > 50%bufferSize";
                // Envio paquete.
                send(appPkt, "toApp");

            } else if (delay != 0 && avgDelay != 0) {
            // Si delay y avgDelay son distintos a su valor inicial.
                // Calculo el porcentaje de diferencia de delay en avgDelay
                // Se busca que
                // delay == avgDelay + avgDelay*aux
                // despejando aux se consigue lo sig:
                aux = (delay - avgDelay)/avgDelay;
                
                if (aux > par("errPercent").doubleValue() || 
                    aux < -par("errPercent").doubleValue()) {
                // Si el porcentaje de diferencia es mayor al 
                // modulo del error aceptado
                    // Creamos paquete para enviar en la App
                    cPacket *appPkt = new cPacket("app_packet");
                    // Se setea su tipo en 1
                    appPkt->setKind(1);
                    if (aux > 0) {
                    // Si el porcentaje de diferencia es positivo.
                        // Se guarda en el paquete el porcentaje 
                        // a solicitar subir.
                        appPkt->addPar("delayAlert") = 
                        aux.dbl(); 
                        //appPkt->addPar("delayAlert") = aux.dbl(); //199526
                        // Campo de debuggeo
                        appPkt->addPar("campus") = "aux > 0"; //199174
                    } else {
                    // Si el porcentaje de diferencia es negativo
                        // Se guarda en el paquete el porcentaje
                        // a solicitar bajar
                        appPkt->addPar("delayAlert") = 
                        -aux.dbl();
                        //appPkt->addPar("delayAlert") = aux.dbl();
                        // Campo de debuggeo
                        appPkt->addPar("campus") = "aux < 0";
                    }
                    // Envio paquete.
                    send(appPkt, "toApp");
                } else if (prevPktTime != 0){
                // Si el porcentaje de dif entra dentro del error aceptado
                // y el prevPktTime es distinto al valor inicial
                    if (prevPktTime+delay*par("errPercent")
                        <= pktTime) {
                    //Si el tiempo de llegada del paquete anterior mas el
                    //delay es menor al tiempo de llegada del paq.
                    //actual.
                    //Quiere decir que el TransportTx envia paquetes mas lento
                    //de lo que puede
                        // Creo paquete a enviar
                        cPacket *appPkt = new cPacket("app_packet");
                        // Su tipo sera 1
                        appPkt->setKind(1);
                        // Se guarda en el paquete el porcentaje
                        // a solicitar bajar
                        appPkt->addPar("delayAlert") = 
                        -par("fixPercent").doubleValue();
                        // Seteo campo de debuggeo
                        appPkt->addPar("campus") = "outro";
                        // Envio paquete.
                        send(appPkt, "toApp");
                    }
                }
            }
            // Calculo el promedio de la lista delay
            countAvg();
            // Guardo el tiempo de llegada del paquete recibido.
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
    // Guardo en lista auxiliar copia de delays.
    cQueue *aux = delays.dup();
    // Creo paquete para iterar elementos
    cPacket *del_pkt;
    // Variables para computar suma
    simtime_t sum = 0;
    // Guardo longitud de cola
    int length = 0;
    while (!aux->isEmpty()) {
    // Mientras haya elementos en la cola
        // Quito el primer elemento y lo guardo
        del_pkt = (cPacket*) aux->pop();
        if (del_pkt->hasPar("delay")) {
        // Si existe el campo delay
            // Se suma el delay
            sum += del_pkt->par("delay").doubleValue();
            // Se cuenta el elemento
            length++;
        } else {
        // si no existe no guarda nada
            sum += 0;
        }
        delete(del_pkt);
    }
    //Se calcula el promedio en variable global
    avgDelay = sum / length;
    //Se borra lista auxiliar.
    aux->~cQueue();
}
    
#endif /* QUEUE */
