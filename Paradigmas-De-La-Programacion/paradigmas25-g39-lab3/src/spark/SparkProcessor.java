package spark;

import java.io.Serializable;

import org.apache.spark.SparkConf;
import org.apache.spark.api.java.JavaSparkContext;
import org.apache.spark.sql.SparkSession;

public abstract class SparkProcessor implements Serializable{
    protected String sparkConfig;

    /**
     * Inicializa una sesion de spark
     * @return SparkSession configurada y lista para usar
    */
    protected SparkSession sparkStart() {
        SparkSession session = SparkSession
        	.builder()
			.appName("FeedProcessor")
			.master(this.sparkConfig)
			.getOrCreate();
            
        return session;
    }

    /**
     * Termina el context spark.
     * @param JavaSparkContext: El contexto que queremos cerrar.
    */
    protected void contextStop(JavaSparkContext context){
        context.stop();
    }
}