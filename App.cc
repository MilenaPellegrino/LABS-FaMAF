#ifndef APP
#define APP

#include <string.h>
#include <omnetpp.h>
#include <packet_m.h>

using namespace omnetpp;

class App: public cSimpleModule {
private:
    cMessage *sendMsgEvent;
    cStdDev delayStats;
    cOutVector delayVector;
    cStdDev jumpsStats;
public:
    App();
    virtual ~App();
protected:
    virtual void initialize();
    virtual void finish();
    virtual void handleMessage(cMessage *msg);
};

Define_Module(App);

#endif /* APP */

App::App() {
}

App::~App() {
}

void App::initialize() {

    // If interArrivalTime for this node is higher than 0
    // initialize packet generator by scheduling sendMsgEvent
    if (par("interArrivalTime").doubleValue() != 0) {
        sendMsgEvent = new cMessage("sendEvent");
        scheduleAt(par("interArrivalTime"), sendMsgEvent);
    }

    // Initialize statistics
    delayStats.setName("TotalDelay");
    delayVector.setName("Delay");
    jumpsStats.setName("Jumps");

}

void App::finish() {
    // Record statistics
    recordScalar("Average delay", delayStats.getMean());
    recordScalar("Number of packets", delayStats.getCount());
    recordScalar("Max hops", jumpsStats.getMax());
    recordScalar("Min hops", jumpsStats.getMin());
}

void App::handleMessage(cMessage *msg) {

    // Paquete de testeo 
    if (canSendTestPacket()){
        // Creamos el paquete de testeo
        // Al packet hay que pasarle un kind, por ahora le puse -1, para que sea diferente a todos, pero no se si es lo correcto 
        Packet *pkt = new Packet("testeo", -1); 
        pkt->setByteLength(par("packetTesteoByteSize"));  // Capaz le erre con el byte size (ver en .ned)
        pkt->setSource(this->getParentModule()->getIndex());  // El source es para indicar que nodo creo el paquete
        pkt->setDestination(par("destination"));  // Que nodo es el destino del paquete
        pkt->addPar("Jumps") = 0;  // Como recien creamos un paquete, la cantidad de nodos por lo que paso es 0.

        // Hay un campo en packet que es hopCount  pero por lo que lei en el codigo no lo usa nunca. 
        // Yo creo que en vez de pkt->addPar("Jumps") = 0;  que por lo que entendi lo que hace es crear una variable nueva al packet en tiempo de ejecucion
        // Tendriamos que setear el campo de hopCount, pero lo deje con el addPar ya que es lo que hace el codigo dado por la catedra. PREGUNTAR 

        // send to net layer
        send(pkt, "toNet$o");


        // FALTA EL SCHEDULE (capaz que haya que poner otro tiempo diferente, es el "x" de nuestra implementacion)
    }

    // if msg is a sendMsgEvent, create and send new packet
    if (msg == sendMsgEvent) {
        // create new packet
        Packet *pkt = new Packet("packet",this->getParentModule()->getIndex());
        pkt->setByteLength(par("packetByteSize"));
        pkt->setSource(this->getParentModule()->getIndex());
        pkt->setDestination(par("destination"));
        pkt->addPar("Jumps") = 0;

        // send to net layer
        send(pkt, "toNet$o");

        // compute the new departure time and schedule next sendMsgEvent
        simtime_t departureTime = simTime() + par("interArrivalTime");
        scheduleAt(departureTime, sendMsgEvent);

    }
    // else, msg is a packet from net layer
    else {
        // compute delay and record statistics
        simtime_t delay = simTime() - msg->getCreationTime();
        long jumps = msg->par("Jumps").longValue();
        delayStats.collect(delay);
        delayVector.record(delay);
        jumpsStats.collect(jumps);
        // delete msg
        delete (msg);
    }

}
