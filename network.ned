simple Generator
{
    parameters:
        volatile double generationInterval; // sec
        @display("i=block/source");
    gates:
        output out;
}

simple Queue
{
    parameters:
        volatile double serviceTime; // sec
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

network Network
{
    @display("bgl=2");
    submodules:
        gen: Generator {
            @display("p=30,30");
        }
        queue: Queue {
            @display("p=130,30");
        }
        sink: Sink {
            @display("p=230,30");
        }
    connections:
        gen.out --> queue.in;
        queue.out --> sink.in;
}
