package namedEntity.heuristic;

import java.util.Map;

public abstract class Heuristic {

	private static Map<String, String> categoryMap = Map.of(
			"Microsoft", "Company", 
			"Apple", "Company", 
			"Google", "Company",
			"Musk", "Person",
			"Biden", "Person",
			"Trump", "Person",
			"Messi", "Person",
			"Federer", "Person",
			"USA", "Country",
			"Russia", "Country"
			);
	
	
	public String getCategory(String entity){
		return categoryMap.get(entity);
	}
	
	
	public abstract boolean isEntity(String word);
		
}
