
package HttpRequest;

import java.net.URI;
import java.net.http.HttpClient;
import java.net.http.HttpRequest;
import java.net.http.HttpResponse;
import java.time.Duration;
import java.io.IOException;
import java.io.UncheckedIOException;
import java.io.InputStream;

public class HttpRequester {
	
	private HttpClient client;

	// Tiempo de espera para la respuesta
	private static final Duration TIMEOUT = Duration.ofSeconds(30);

	/**
  	* Constructor para HttpRequester, inicializa el cliente.
  	* Inicializa un cliente HTTP interno (HttpClient) con configuración predeterminada
  	* (HTTP/2, sigue redirecciones, timeout de conexión).
  	*
  	* @throws IllegalArgumentException Si ocurre un problema con los argumentos al construir el cliente.
	* @throws UncheckedIOException Si ocurre un error de I/O al inicializar el cliente.
  	* @throws SecurityException Si hay restricciones de seguridad que impiden crear el cliente.
  	*/

	public HttpRequester() {
		try {	// Inicializamos el cliente HTTP
				this.client = HttpClient.newBuilder()
				.version(HttpClient.Version.HTTP_2) // Usamos HTTP/2 (si el servidor lo soporta)
				.followRedirects(HttpClient.Redirect.NORMAL) // Seguir redirecciones
				.connectTimeout(TIMEOUT) //Establece el timeout
				.build();
		} catch (IllegalArgumentException e) {
			System.err.println("ERROR: " + e.getMessage());
			this.client = null;
			throw e; //Lanzo la Exception para arriba
		} catch (UncheckedIOException e) {
			System.err.println("ERROR: " + e.getMessage());
			this.client = null;
			throw e;
		} catch (SecurityException e) {
			System.err.println("ERROR: " + e.getMessage());
			this.client = null;
			throw e;
		}		
	}

	/**
	 * Realiza las peticiones HTTP
	 * @param url  La URL a la que se le hace la peticion
	 * @return Un InputStream con el cuerpo de respuesta. En llamador es encargado de cerrarlo.
	 * @throws IllegalArgumentException Si la URL es nula/vacía o el cliente no está inicializado.
	 * @throws IllegalStateException Si la respuesta del servidor no es 200 OK.
	 * @throws RuntimeException Si ocurre cualquier otro error durante la petición.
	 */
	public InputStream getFeed(String url) {
		
		//Instancio un response para retornarlo más tarde y no tener multiples return
		HttpResponse<InputStream> response;

		// Verificamos que la URL sea correcta y que client no sea null
		if (url == null || url.isEmpty() || this.client == null){
			throw new IllegalArgumentException();
		}

		// Realizamos la peticion en try_catch
		try{
			// Cresamos la peticion HTTP
			HttpRequest request = HttpRequest.newBuilder()
				.uri(URI.create(url))  // URL al que se le hace la peticion
				.timeout(TIMEOUT)  // Tiempo de espera para la respuesta (30s)
				.GET()  // Metodo GET porque queremos obtener datos 
				.build();

			//  Enviamos la peticion y obtenemos la respuesta en un InputString
			response = client.send(request, HttpResponse.BodyHandlers.ofInputStream());

			// Verificamos el codigo de respuesta 
			if (response.statusCode() != 200){
				System.err.println("Error en la peticion HTTP a la direccion: " + url +
									" Código de error: " + response.statusCode());
            	throw new IllegalStateException();
			}

			//-----------------MANEJO DE EXCEPTIONS-----------------------
			//RunTimeExceptio es una exception de tipo No Chequeada. Esto quiere decir que se deben
			//A errores de programación o condiciones inesperadas en tiempo de ejecución.
			//El punto de estas exceptions es que no necesitan estar en la firma del método, por ejemplo:
			//public String getFeed(String url) throws Exception {...}

			//Es como un sobre que sirve para guardar la Exception original(e) y hacer que se
			//propague en la pila de llamadas.
			//IMPORTANTE:
			//Si se llama a esté método, el catch tiene que ser:
			//Catch (RunTimeException)
			//Y para acceder a la Exception original(e), se puede acceder como
			//(variable RunTimeException).getCause

		} catch (IOException e) {
			System.err.println("Error: Problema con I/O u el cliente cerró la conexión " + e.getMessage());
			// Envolvemos la excepción original en una RuntimeException
			throw new RuntimeException("Error de I/O durante la petición a " + url, e);
		} catch (IllegalArgumentException e){
			// Esta podría ser lanzada por URI.create() si la URL tiene formato inválido
			System.err.println("Error: Argumento no válido " + e.getMessage());
			throw new RuntimeException("Argumento inválido, posiblemente la URL: " + url, e);
		} catch (InterruptedException e){
			System.err.println("Error: La operación ha sido interrumpida " + e.getMessage());
			// Es buena práctica restaurar el estado de interrupción
			Thread.currentThread().interrupt();
			throw new RuntimeException("La petición fue interrumpida para " + url, e);
		} catch (IllegalStateException e) {
			// Esta puede ser lanzada por nosotros (status != 200) o por HttpClient
			System.err.println("Error: Uri no se pudo crear " + e.getMessage());
			// Re-lanzamos la misma o la envolvemos si queremos añadir contexto
			throw new RuntimeException("Estado ilegal durante la petición a " + url, e);
		} catch (SecurityException e) {
			System.err.println("Error: Se negó el acceso al Url " + e.getMessage());
			throw new RuntimeException("Acceso denegado por seguridad para " + url, e);
		} catch (Exception e) {
			// Captura genérica para cualquier otra cosa inesperada
			System.err.println("Error: Ocurrió una exception " + e.getMessage());
			throw new RuntimeException("Error inesperado durante la petición a " + url, e);
		}
		return response.body();
	}

	//TESTS
	//Se podría usar un framework como JUnit pero creo que es demasiado para testear clases "tan simples"
	public static void main(String[] args) {
		System.err.println("------INICIANDO DEMOSTRACIÓN(Que si funciona)------");
		HttpRequester requester = new HttpRequester();
		//ESTO DEBERÍA FUNCIONAR
		String urlToRequest = "https://rss.nytimes.com/services/xml/rss/nyt/Business.xml";
		System.err.println("Intentando obtener el contenido: " + urlToRequest);
		//Uso try_whit_resources para asegurarme que el InputStream sea cerrado
		try (InputStream rssStream = requester.getFeed(urlToRequest)) {
			//SALE BIEN
			System.err.println("--> Éxito obteniendo el InputStream con el contenido de RSS");
			//Si se quieren revisar los primeros n bytes:
			//byte[] buffer = new byte[20];
			//int bytesRead = rssStream.read(buffer);
			//System.out.println("   Primeros bytes (como string): " + new String(buffer, 0, bytesRead));


			//FUNCIONA CON REDDIT?
			urlToRequest = "https://www.reddit.com/r/Marketing/hot/.json?count=100";
			System.err.println("Intentando obtener el contenido: " + urlToRequest);
			try (InputStream redditStream = requester.getFeed(urlToRequest)) {
				System.err.println("--> Éxito obteniendo el InputStream con el contenido de Reddit");
				//Si se quieren revisar los primeros n bytes:
				// byte[] buffer = new byte[n];
				// int bytesRead = redditStream.read(buffer);
				// System.out.println("   Primeros bytes (como string): " + new String(buffer, 0, bytesRead));
			}
		} catch (IllegalArgumentException e) {
			System.err.println("ERROR: Url nula o cliente no inicializado " + e.getMessage());
		} catch (IllegalStateException e){
			System.err.println("ERROR: El servidor no dió code 200 " + e.getMessage());
		} catch (RuntimeException e) {
			System.err.println("ERROR: Error en tiempo de ejecución: " + e.getMessage());
			if (e.getCause() != null) {
				System.err.println("    Causa original: " + e.getCause().getClass().getSimpleName() + " " +e.getCause().getMessage());
			}
		} catch (IOException e) {
			System.err.println("ERROR: Ocurrio un error de I/O: " + e.getMessage());
		}
	}
}
