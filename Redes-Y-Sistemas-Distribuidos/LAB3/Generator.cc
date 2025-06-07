#ifndef GENERATOR
#define GENERATOR

#include <string.h>
#include <omnetpp.h>

using namespace omnetpp;

class Generator : public cSimpleModule {
private:
    cMessage *sendMsgEvent;
    cStdDev transmissionStats;
    cOutVector packetGenVector;
public:
    Generator();
    virtual ~Generator();
protected:
    virtual void initialize();
    virtual void finish();
    virtual void handleMessage(cMessage *msg);
};
Define_Module(Generator);

Generator::Generator() {
    sendMsgEvent = NULL;

}

Generator::~Generator() {
    cancelAndDelete(sendMsgEvent);
}

void Generator::initialize() {
    packetGenVector.setName("packetGen");
    transmissionStats.setName("TotalTransmissions");
    // create the send packet
    sendMsgEvent = new cMessage("sendEvent");
    // schedule the first event at random time
    scheduleAt(par("generationInterval"), sendMsgEvent);
}

void Generator::finish() {
}

void Generator::handleMessage(cMessage *msg) {

    // create new packet
    cPacket *pkt;
    pkt = new cPacket("packet");
    packetGenVector.record(1);
    pkt->setByteLength(par("packetByteSize").doubleValue());
    // Se pone con tipo 0
    pkt->setKind(0);
    // pkt->encapsulate(msg);
    //cMessage *pkt = new cMessage("packet"); 
    // send to the output
    send(pkt, "out");

    // compute the new departure time
    simtime_t departureTime = simTime() + par("generationInterval");
    
    // schedule the new packet generation
    scheduleAt(departureTime, sendMsgEvent);
}

#endif /* GENERATOR */
