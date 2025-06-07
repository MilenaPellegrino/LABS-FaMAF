package parser;

// import feed.Article;
// import feed.Feed;
// import org.json.JSONArray;
// import org.json.JSONObject;

// import java.util.Date;

// /*
//  * Esta clase implementa el parser de feed de tipo reddit (json)
//  * pero no es necesario su implemntacion 
//  * */

// /*
// Siguiendo la siguente documentacion:
// https://www.reddit.com/dev/api/
// https://www.jcchouinard.com/documentation-on-reddit-apis-json/
//  */

// public class RedditParser extends GeneralParser<Feed>{

//     /**
//      * Parsea un JSON en fomrato Reddit y lo convierte en un objeto Feed
//      * 
//      * Suponiendo que el JSON tiene la estructura tipico de la responde de reddit (la ofrecida por la API)
//      * Es decir, que tiene un objeto data que contiene un array de objetos children
//      * y cada objeto children tiene un objeto data que contiene los atributos title, selftext, url y created_utc
//      * 
//      * @param jsonString el JSON en formato Reddit como String 
//      * @return un objeto Feed que contiene la lista de los articulos)
//      */
//     public Feed parse(String jsonString){
//         JSONObject jsonObject = new JSONObject(jsonString);
//         JSONObject data = jsonObject.getJSONObject("data");
//         JSONArray children = data.getJSONArray("children");
        
//         Feed feed = new Feed("Reddit");

//         for (int i = 0; i < children.length(); i++) {
//             JSONObject child = children.getJSONObject(i);
//             JSONObject childData = child.getJSONObject("data");
            
//             String title = childData.getString("title");
//             String text = childData.getString("selftext");
//             String link = childData.getString("url");

//             long createdUtc = childData.getLong("created_utc");
//             Date publicationDate = new Date(createdUtc * 1000);
            
//             Article article = new Article(title, text, publicationDate, link);
//             feed.addArticle(article);
//         }
//         return feed;
//     }
// }
