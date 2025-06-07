import feed.*;
import parser.*;
import subscription.*;
import HttpRequest.*;
import namedEntity.heuristic.*;
import namedEntity.*;
import java.util.Comparator;
import java.util.List;
import java.util.ArrayList;
import java.io.InputStream;
import java.io.FileInputStream;

public class FeedReaderMain {

	private static void printHelp(){
		System.out.println("Please, call this program in correct way: FeedReader [-ne]");
	}

	private static void processFeed(Feed feed, QuickHeuristic heur, List<NamedEntity> entList, List<String> wrdList) {
		for (Article article : feed.getArticleList()) {
			processArticle(article, heur, entList, wrdList);
		}
	}

	private static void processArticle(Article article, QuickHeuristic heur, List<NamedEntity> entList, List<String> wrdList) {
		String[] words = article.getText().split(" ");
		for (String word : words) {
			processWord(word, heur, entList, wrdList);
		}
	}

	private static void processWord(String word, QuickHeuristic heur, List<NamedEntity> entList, List<String> wrdList) {
		if (!heur.isEntity(word)) return;

		if (!wrdList.contains(word)) {
			wrdList.add(word);
			String category = heur.getCategory(word);
			entList.add(new NamedEntity(word, category, 1));
		} else {
			for (NamedEntity entity : entList) {
				if (word.equals(entity.getName())) {
					entity.incFrequency();
					break;
				}
			}
		}
	}
	
	public static void main(String[] args) {
	System.out.println("************* FeedReader version 1.0 *************");

	SubscriptionParser parser = new SubscriptionParser();
	InputStream input = null;
	try {
		input = new FileInputStream("config/subscriptions.json");
		Subscription subscriptions = parser.parse(input);

		if (args.length == 0) {
			for (SingleSubscription sub : subscriptions.getSubscriptionsList()) {
				if (sub.getUrlType().equals("rss")) {
					for (int i = 0; i < sub.getUlrParamsSize(); i++) {
						HttpRequester req = new HttpRequester();
						String url = sub.getFeedToRequest(i);
						input = req.getFeed(url);
						RssParser rssParser = new RssParser();
						Feed feed = rssParser.parse(input);
						feed.prettyPrint();
					}
				} else if (sub.getUrlType().equals("reddit")) {
					// Implementar reddit
				}
			}
		} else if (args.length == 1 && args[0].equals("-ne")) {
			List<Feed> feedList = new ArrayList<>();
			for (SingleSubscription sub : subscriptions.getSubscriptionsList()) {
				if (sub.getUrlType().equals("rss")) {
					for (int i = 0; i < sub.getUlrParamsSize(); i++) {
						HttpRequester req = new HttpRequester();
						String url = sub.getFeedToRequest(i);
						input = req.getFeed(url);
						RssParser rssParser = new RssParser();
						Feed feed = rssParser.parse(input);
						feedList.add(feed);
					}
				}
			}

			QuickHeuristic heur = new QuickHeuristic();
			List<String> wrdList = new ArrayList<>();
			List<NamedEntity> entList = new ArrayList<>();

			for (Feed feed : feedList) {
				processFeed(feed, heur, entList, wrdList);
			}

			entList.sort(Comparator.comparingInt(NamedEntity::getFrequency).reversed());
			System.out.printf("%-20s %10s%n", "Entidad", "Frecuencia");
			System.out.println("-------------------- ----------");
			for (NamedEntity entity : entList) {
				System.out.printf("%-20s %10d%n", entity.getName(), entity.getFrequency());
			}
		} else {
			printHelp();
		}
	} catch (Exception e) {
		e.printStackTrace();
	}
}


}