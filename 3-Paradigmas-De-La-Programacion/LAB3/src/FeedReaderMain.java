// Nuestros imports
import feed.*;
import parser.*;
import spark.*;
import subscription.*;
import HttpRequest.*;
import namedEntity.heuristic.*;
import namedEntity.*;

import java.util.*;
import java.util.stream.Collectors;
import java.io.InputStream;
import java.io.FileInputStream;

public class FeedReaderMain {

	/**
	 * En caso de no coicidir con los argumentos de entrada, imprime como utilizar el programa
	*/
	private static void printHelp(){
		System.out.println("Please, call this program in correct way: FeedReader [-ne]");
	}
	
	/**
	 * Método principal de la clase
	 * @param args Los argumentos del programa
	  */
	public static void main(String[] args) {
	System.out.println("************* FeedReader version 2.0 *************");


		SubscriptionParser parser = new SubscriptionParser();
		InputStream input = null;
		
		try {
			input = new FileInputStream("config/subscriptions.json");
			Subscription subscriptions = parser.parse(input);

			String config = "local[*]";
			//String config = "spark://localhost:7077";
			
			if (args.length == 0) {  // Se imprimen los feeds completos
				SparkSubscriptionProcessor processor = new SparkSubscriptionProcessor(config, subscriptions);
				List<Feed> feedList = new ArrayList<>();

				feedList = processor.processSubs();
				for (Feed feed: feedList) {
					feed.prettyPrint();
				}

			} else if (args.length == 1 && args[0].equals("-ne")) {  // Se imprimen la cantidad de entidades encontradas usando heuristicas
				SparkSubscriptionProcessor processor1 = new SparkSubscriptionProcessor(config, subscriptions);
				List<Feed> feedList = new ArrayList<>();
				feedList = processor1.processSubs();
				
				//QuickHeuristic heur = new QuickHeuristic();
				//RandomHeuristic heur = new RandomHeuristic();
				SuperHeuristic heur = new SuperHeuristic();
				
				SparkNamedEntityProcessor processor2 = new SparkNamedEntityProcessor(feedList, heur, config);
				Map<String, Long> heurMap = processor2.processEntity();

				Map<String, Long> heurMapSorted = heurMap.entrySet()
    				.stream()
    				.sorted(Map.Entry.<String, Long>comparingByValue().reversed())
    				.collect(Collectors.toMap(
        				Map.Entry::getKey,  // obtener la clave
        				Map.Entry::getValue,  // obtener el valor
        				(e1, e2) -> e1,  // para las claves duplicadas (no tendria que haber, pero es buena practica)
        				LinkedHashMap::new  // mantener el orden al collector
    					));

				System.out.printf("%-20s %10s%n", "Entidad", "Frecuencia");
				System.out.println("-------------------- ----------");
				for (Map.Entry<String, Long> entry : heurMapSorted.entrySet()) {
					System.out.printf("%-20s %10d%n", entry.getKey(), entry.getValue());
				}
			}  else {
				printHelp();
			} 
		}catch (Exception e){
			System.err.println("Ocurrió un error en tiempo de ejecución");

		}
	}
}
