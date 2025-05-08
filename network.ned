// Este es el segundo archivo que se ejecuta.
// /*
// A continuacion se crean miembros de la clase cSimpleModule
// Su configuracion se vera marcada por los modulos NodeRx, NodeTx, y Network
// Su funcionamiento es definido en el archivo de mismo_nombre_al_miembro.cc
// Ver Queue.cc para mas detalles, los demas mantienen el mismo formato.
// */

//Anotare en detalle el primer miembro, los demas siguen el mismo formato.

// Miembro Generator, encargado de la creacion de paquetes
simple Generator
{
    parameters:
        // Una suerte de referencia a parametros generales definidos en el .ini
        volatile double generationInterval; // sec
        volatile double packetByteSize; // bytes
        
        // Indica como debe visualizarse el modulo en la interfaz omnet
        // @display("TipoDeElemento=Forma/Icono")
        @display("i=block/source");

    gates:
        // Indica que dicho miembro tiene una conexion de salida.
        output out;
}

// Miembro Queue, encargado de recibir, enlistar, y enviar paquetes
simple Queue
{
    parameters:
        // volatile double serviceTime; // sec
        volatile double bufferSize; // bytes
        
        
        @display("i=block/queue;q=buffer");
    gates:
        input in;
        output out;
}

// Miembro Sink, encargado de ser el destino.
simple Sink
{
    parameters:
        @display("i=block/sink");
    gates:
        input in;
}


///*
//A continuacion empiezan los modulos.
//Definen la configuracion general de la network.
//*/

//Anotare en detalle el primer modulo, los demas siguen el mismo formato.

// Modulo NodeTx encargado de abstraer la conexion entre Generator y Queue.
module NodeTx
{
    parameters:
        @display("i=block/routing");
    gates:
        output out;

    // Submodulos que hacen referencia a los modulos Simples definidos arriba.
    submodules:
        gen: Generator {
            parameters:
                @display("p=75,50");
        }
        queue: Queue {
            parameters:
                @display("p=75,190");
        }
        // Se establecen las conexiones entre submodulos.
        connections:
            gen.out --> queue.in;
            queue.out --> out;
}

// Modulo NodeRx encargado de abstraer la conexion entre Queue y Sink.
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
                queue.out --> { datarate = 0.5Mbps; } --> sink.in;
                //case study 2
                //queue.out --> { datarate = 1Mbps; } --> sink.in;
}

// Modulo Network principal, se encarga de manejar el comportamiento de la red.
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
            // Observar que entre {} esta definida la tasa de datos y el
            // retardo en envio de paquetes dentro de esa conexion.
            nodeTx.out --> { datarate = 1Mbps; delay = 100us; } --> queue.in;
            //case study 1
            queue.out --> { datarate = 0.5Mbps; } --> nodeRx.in;
            //case study 2
            //queue.out --> { datarate = 0.5Mbps; delay = 100us; } --> nodeRx.in;
}