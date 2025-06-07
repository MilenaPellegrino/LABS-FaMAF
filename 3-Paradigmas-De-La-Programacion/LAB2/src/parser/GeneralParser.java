package parser;

import java.io.InputStream;
 
/*Esta clase modela los atributos y metodos comunes a todos los distintos tipos de parser existentes en la aplicacion*/
public abstract class GeneralParser<T> {

    //Aquí agregar los atributos comunes a los parser
    //Private tipoDelAtributo nombreDelAtributo;

    /**
     * Es una clase abstracta que parsea datos de entrada
     * y los convierte en el Objeto de tipo T.
     * @param inputStream El contenido crudo a parsear
     * @return Un objeto de tipo T representando los datos.
     */
    
     public abstract T parse(InputStream inputStream);

}
