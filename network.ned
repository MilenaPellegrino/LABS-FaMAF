simple Generator
{
    parameters:
        volatile double generationInterval; // sec
        volatile double packetByteSize; // bytes
        @display("i=block/source");
    gates:
        output out;
}

simple Queue
{
    parameters:
        volatile double serviceTime; // sec
        volatile double bufferSize; // bytes
        @display("i=block/queue;q=buffer");
    gates:
        input in;
        output out;
}

simple Sink
{
    parameters:
        @display("i=block/sink");
    gates:
        input in;
}

//network Network
//{
//    @display("bgl=2");
//    submodules:
//        gen: Generator {
//            @display("p=30,30");
//        }
//        queue: Queue {
//            @display("p=130,30");
//        }
//        sink: Sink {
//            @display("p=230,30");
//        }
//    connections:
//        gen.out --> queue.in;
//        queue.out --> sink.in;
//}

module NodeTx
{
    parameters:
        @display("i=block/routing");
    gates:
        output out;
    submodules:
        gen: Generator {
            parameters:
                @display("p=75,50");
        }
        queue: Queue {
            parameters:
                @display("p=75,190");
        }
        connections:
            gen.out --> queue.in;
            queue.out --> out;
}

module NodeRx
{
    parameters:
        @display("i=block/routing");
    gates:
        input in;
    submodules:
        sink: Sink{
            parameters:
                @display("p=75, 50");
            }
            queue: Queue {
                parameters:
                    @display("p=75, 190");
            }
            connections:
                in --> queue.in;
                //case study 1
                //queue.out --> { datarate = 0.5Mbps; } --> sink.in;
                //case study 2
                queue.out --> { datarate = 1Mbps; } --> sink.in;
}

network Network
{
    @display("bgl=2");
    submodules:
        nodeTx: NodeTx {
            @display("p=30,30");
        }
        queue: Queue {
            @display("p=130,30");
        }
        nodeRx: NodeRx {
            @display("p=230,30");
        }
        connections:
            nodeTx.out --> { datarate = 1Mbps; delay = 100us; } --> queue.in;
            //case study 1
            //queue.out --> { datarate = 0.5Mbps; } --> nodeRx.in;
            //case study 2
            queue.out --> { datarate = 0.5Mbps; delay = 100us; } --> nodeRx.in;
}