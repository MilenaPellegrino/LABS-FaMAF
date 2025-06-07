package spark;

//Imports de Spark
import org.apache.spark.SparkConf;
import org.apache.spark.sql.SparkSession;
import org.apache.spark.api.java.JavaSparkContext;
import org.apache.spark.api.java.JavaRDD;
import org.apache.spark.api.java.JavaPairRDD;
import org.apache.spark.api.java.function.*;
//Imports java
import java.io.InputStream;
import java.util.*;
import scala.Tuple2;
//Imports nuestros
import subscription.*;
import feed.*;
import HttpRequest.*;
import parser.*;
import namedEntity.heuristic.*;
import namedEntity.*;

public class SparkNamedEntityProcessor extends SparkProcessor {
    private List<Feed> listFeed;
    private Heuristic heuristic;

	/**
	 * Constructor de la clase
	 * @param listFeed
	 * @param heuristic
	 * @param sparkConfig
	  */
    public SparkNamedEntityProcessor(List<Feed> listFeed, Heuristic heuristic, String sparkConfig){
        this.listFeed = listFeed;
        this.heuristic = heuristic;
		this.sparkConfig = sparkConfig;
    }

	/**
	 * Extraemos todos los articulos de todos los feeds en una lista
	 * @return Lista con todos los articulos de nuestra lista de feeds.
	 * @throws RuntimeException Si ocurre un error en ejecución
	 */
	private List<Article> processFeed(){
		List<Article> listArticle = new ArrayList<>();
		try {
			for(Feed feed : this.listFeed){
				listArticle.addAll(feed.getArticleList());
			}
		return listArticle;
		} catch (Exception e) {
			throw new RuntimeException("Error inesperado durante la ejecución", e);
		}
	}
	/**
	 * Método que usa computación distribuida para calcular las entidades nombradas en los articulos.
	 * @return Un map<String, Long> que contiene <nombre de entidad, frecuencia>.
	 * @throws RuntimeException Si ocurre un error en tiempo de ejecución.
	*/
    public Map<String, Long> processEntity(){
		try {
			//Levantamos sesión y creamos el context
			SparkSession session = this.sparkStart();
			JavaSparkContext jsc = new JavaSparkContext(session.sparkContext());
			//Creamos el primer RDD de articulos
			JavaRDD<Article> articleRDD = jsc.parallelize(this.processFeed());
			//Computamos los entities con flatmap
			JavaRDD<NamedEntity> listEntityRDD = articleRDD.flatMap(
				article -> {
					article.computeNamedEntities(this.heuristic);
					return article.getNamedEntityList().iterator();
				}
			);
			//Lo pasamos a un pairRDD
			JavaPairRDD<String, Long> pairEntity = listEntityRDD.mapToPair(
				(PairFunction<NamedEntity, String, Long>) entity -> new Tuple2<>(entity.getName(), (long) entity.getFrequency())
			);
			//Esto es para contar las entidades con el mismo nombre en distintos articulos
			JavaPairRDD<String, Long> entityCounts = pairEntity.reduceByKey(
				(Function2<Long, Long, Long>) (v1, v2) -> v1 + v2
			);
			//Recolectamos los resultados
			Map<String, Long> resultado = entityCounts.collectAsMap();
			//Cerramos el context, lo cuál cierra también automaticamente la sesion
			this.contextStop(jsc);
			//Retornamos el resultado
			return resultado;
		} catch (Exception e) {
			throw new RuntimeException("Ocurrió un error en la ejecución", e);
		}
    }
}