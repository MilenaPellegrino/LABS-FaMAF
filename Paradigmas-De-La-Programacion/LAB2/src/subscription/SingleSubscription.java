package subscription;

import java.util.ArrayList;
import java.util.List;


/*Esta clse abstrae el contenido de una sola suscripcion que ocurre en lista de suscripciones que figuran en el archivo de suscrpcion(json) */
public class SingleSubscription {
	
	private String url;
	private List<String> ulrParams;
	private String urlType;
	
	
	public SingleSubscription(String url, List<String> ulrParams, String urlType) {
		super();
		this.url = url;
		this.ulrParams = ulrParams;
		this.urlType = urlType;
	}

	public String getUrl() {
		return url;
	}
	public void setUrl(String url) {
		this.url = url;
	}
	public List<String> getUlrParams() {
		return ulrParams;
	}
	public String getUlrParams(int i) {
		return this.ulrParams.get(i);
	}
	public void setUlrParams(String urlParam) {
		this.ulrParams.add(urlParam);
	}
	public int getUlrParamsSize() {
		return ulrParams.size();
	}
	public String getUrlType() {
		return urlType;
	}
	public void setUrlType(String urlType) {
		this.urlType = urlType;
	} 
	
	@Override
	public String toString() {
		return "{url=" + getUrl() + ", ulrParams=" + getUlrParams().toString() + ", urlType=" + getUrlType() + "}";
	}
	
	public void prettyPrint(){
		System.out.println(this.toString());
	}
	
	
	public String getFeedToRequest(int i){
		return this.getUrl().replace("%s",this.getUlrParams(i));
	}
	
	public static void main(String[] args) {
		System.out.println("SingleSubscriptionClass");
		SingleSubscription s = new SingleSubscription("https://rss.nytimes.com/services/xml/rss/nyt/%s.xml", null, "rss");
		s.setUlrParams("Business");
		s.setUlrParams("Technology");
		System.out.println(s.getFeedToRequest(0));
		s.prettyPrint();
	}
	
	
	
	
}
