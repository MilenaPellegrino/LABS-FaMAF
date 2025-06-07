package spark;

//Import de spark
import org.apache.spark.SparkConf;
import org.apache.spark.sql.SparkSession;
import org.apache.spark.api.java.JavaSparkContext;
import org.apache.spark.api.java.JavaRDD;
//Imports de java
import java.io.InputStream;
import java.util.*;
//Imports nuestros
import subscription.*;
import feed.*;
import HttpRequest.*;
import parser.*;

public class SparkSubscriptionProcessor extends SparkProcessor {
    private Subscription subs;

    /**
     * Constructor de clase
     * @param sparkConfig
     * @param subs
     */
    public SparkSubscriptionProcessor(String sparkConfig, Subscription subs) {
        this.sparkConfig = sparkConfig;
        this.subs = subs;
    }

    /**
     * Procesa el Subscription computandolo de manera distribuida
     * @return Lista de todos los Feeds.
     * @throws RuntimeException
     */
    public List<Feed> processSubs() {
        try {
            //Creamos la sesión y el context
            SparkSession spark = this.sparkStart();
            JavaSparkContext jsc = new JavaSparkContext(spark.sparkContext());
            //Creamos el primer RDD - "lista" con todas las SingleSubscription's
            JavaRDD<SingleSubscription> singleSubscriptionRDD = jsc.parallelize(this.subs.getSubscriptionsList()); 
            //Hago los pedidos y los agrego a una lista de Feeds que luego aplano para meterlos en el RDD
            JavaRDD<Feed> feedRDD = singleSubscriptionRDD.flatMap(singleSub -> 
                {
                    List<Feed> listFeed = new ArrayList<>();
                    for (int i = 0; i < singleSub.getUlrParamsSize(); i++) {
                        try {
                            HttpRequester req = new HttpRequester();
                            InputStream input = req.getFeed(singleSub.getFeedToRequest(i));
                            RssParser rssParser = new RssParser();
                            Feed feed = rssParser.parse(input);
                            listFeed.add(feed);
                        } catch (Exception e) {
                   			throw new RuntimeException("Error inesperado durante la ejecución", e);
                        }
                    }
                    return listFeed.iterator();
                }
            );
            //Filtramos por si hay algún elemento nulo
            JavaRDD<Feed> filteredFeedRDD = feedRDD.filter(element -> element != null);
            //Recolectamos los resultados en una lista de Feeds
            List<Feed> result = filteredFeedRDD.collect();
            //Cerramos el context de spark
            this.contextStop(jsc);
            //Retornamos la lista de Feeds
            return result;   
        } catch (Exception e) {
            throw new RuntimeException("Ocurrió un error en tiempo de compilación", e);
        }
    }
}
