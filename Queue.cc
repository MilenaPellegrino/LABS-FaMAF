#ifndef QUEUE
#define QUEUE

#include <string.h>
#include <omnetpp.h>

using namespace omnetpp;

class Queue: public cSimpleModule {
private:
    cQueue buffer;
    cMessage *endServiceEvent;
    simtime_t serviceTime;
public:
    Queue();
    virtual ~Queue();
protected:
    virtual void initialize();
    virtual void finish();
    virtual void handleMessage(cMessage *msg);
};

Define_Module(Queue);

Queue::Queue() {
    endServiceEvent = NULL;
}

Queue::~Queue() {
    cancelAndDelete(endServiceEvent);
}

void Queue::initialize() {
    buffer.setName("buffer");
    endServiceEvent = new cMessage("endService");
}

void Queue::finish() {
}

void Queue::handleMessage(cMessage *msg) {

    // if msg is signaling an endServiceEvent
    if (msg == endServiceEvent) {
        // if packet in buffer, send next one
        if (!buffer.isEmpty()) {
            // dequeue packet
            cMessage *pkt = (cMessage*) buffer.pop();
            // send packet
            send(pkt, "out");
            // start new service
            serviceTime = par("serviceTime");
            scheduleAt(simTime() + serviceTime, endServiceEvent);
        }
    } else { // if msg is a data packet
        // enqueue the packet
        buffer.insert(msg);
        // if the server is idle
        if (!endServiceEvent->isScheduled()) {
            // start the service
            scheduleAt(simTime(), endServiceEvent);
        }
    }
}

#endif /* QUEUE */
