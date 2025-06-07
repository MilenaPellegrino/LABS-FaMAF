package parser;

//Puedo estar equivocado pero dejo comentado el código para que por lo menos
//se entienda lo que quiero hacer
import org.json.JSONArray;
import org.json.JSONObject;
import org.json.JSONException;

import subscription.SingleSubscription;
import subscription.Subscription;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.List;


import java.io.InputStream;
import java.io.IOException;
import java.nio.charset.StandardCharsets;

/*
 * Esta clase implementa el parser del  archivo de suscripcion (json)
 * Leer https://www.w3docs.com/snippets/java/how-to-parse-json-in-java.html
 * */

 //Creo una clase SubscriptionParser que hereda de GeneralParser atributos y métodos
public class SubscriptionParser extends GeneralParser<Subscription>{
    /** 
     * Parsea el archivo JSON de suscripciones especificado
     * 
     * @param filePath la ruta al archivo subscriptions.json
     * @return Una lista de objetos SingleSubscription leidos del archivo.
     * Retorna una lista vacía si ocurre un error o el archivo no contiene suscripciones válidas.
    */

    public Subscription parse(InputStream inputStream) {
        //Creo la lista vacia de SingleSubscription(s)
        Subscription subscriptions = new Subscription("input stream");
        
        //Lo hago con try por si explota
        try {
            // Convertir el InputStream en un String (asumiendo UTF-8)
            String content = new String(inputStream.readAllBytes(), java.nio.charset.StandardCharsets.UTF_8);
            
            //Creo una JSONArray con el contenido leido
            JSONArray jsonarray = new JSONArray(content);

            //Itero sobre esa JSONArray
            for (int i = 0; i < jsonarray.length(); i++) {
                //Declaro un JSONObject que representa la suscripción
                JSONObject jsonSubscription = jsonarray.getJSONObject(i);

                //Guardo los parametros en una lista
                JSONArray params = jsonSubscription.optJSONArray("urlParams");
                List<String> paramList = new ArrayList<>();
                if (params != null) {
                    for (int j=0; j < params.length(); j++) {
                        paramList.add(params.getString(j));
                    }
                }
                
                //Creo la SingleSuscripción con gets sobre el JSONObject, si algún get falla
                //debería levantar JSONException
                SingleSubscription sub = new SingleSubscription(jsonSubscription.getString("url"),
                                                                paramList,
                                                                jsonSubscription.getString("urlType"));
                //Por útilmo agrego esa SingleSubscription a la lista de suscripciones
                subscriptions.addSingleSubscription(sub);
            }
        } catch (IOException e) {
            System.err.println("Error al leer el archivo: " + e.getMessage());
        } catch (JSONException e) {
            System.err.println("Error al parsear el JSON: " + e.getMessage());
        }
        return subscriptions;
    }
}