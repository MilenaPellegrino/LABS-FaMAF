package parser;

import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.ParserConfigurationException;
import org.xml.sax.SAXException;

import feed.Feed;
import feed.Article;

import java.io.IOException;
import java.io.InputStream;
import org.w3c.dom.NodeList;
import org.w3c.dom.Node;
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Locale;

public class RssParser extends GeneralParser<Feed> {

    /**
     * Parsea un InputStream con contenido RSS y devuelve un objeto Feed con los artículos.
     * @param inputStream Flujo de entrada con el contenido RSS a parsear.
     * @return Objeto Feed con los artículos encontrados.
     * @throws IllegalArgumentException Si el inputStream es null
     * @throws ParserException Si ocurre un error durante el parseo del RSS
     */

    @Override
    public Feed parse(InputStream inputStream) {
        /*
         * Para parsear el XML usamos DOM. 
         * Pensamos el XML como un arbol de nodos.
         */
        if (inputStream == null) {
            throw new IllegalArgumentException("El inputStream NO puede ser NULL");
        }
        
        // Usamos un nombre generico al crear el feed
        Feed feed = new Feed("RSS Feed");
        
        // Uso try_with_resources para que el InputStream se cierre automaticamente.
        // usando eso, Java me garantiza que se haga stream.close() cuando el try termine o si salta una Exception
        // Tanto stream como InputStream apuntan al mismo objeto InputStream
        // La llamada de close va a ser stream.close() (también se cierra inputStream)
        try (InputStream stream = inputStream) {

            // Configuramos el parser DOM 

            // Creamos una instancia de DocumentBuilderFactory, es lo que nos ayuda a crear objetos que construyen arboles de documentos XML
            DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();

            // DocumentBuild es el que se encarga de parsear el XML y construir el arbol DOM
            DocumentBuilder builder = factory.newDocumentBuilder();

            // Parseo del XML
            Document doc = builder.parse(stream);
            
            // Con normaliz lo que hacemos es limpiar el arbol, para qu eno haya cosas raras
            doc.getDocumentElement().normalize();
            
            // Intentar obtener el título del channel
            try {
                // Devuelve una lista con todos los elementos <channel> del doc. Cada ocurrencia es un Nodo de la lista
                NodeList channelList = doc.getElementsByTagName("channel");
                // Me fijo que no esté vacio, y que el item 0 (el primer <channel> que tiene la info del site) sea un Nodo valido
                if (channelList.getLength() > 0 && channelList.item(0).getNodeType() == Node.ELEMENT_NODE) {
                     // Obtengo el channel que nos interesa parseandolo a Element en vez de Node 
                    // Esto lo podemos hacer gracias a la guarda de nuestro if
                    Element channelElement = (Element) channelList.item(0);

                    //Obtengo el elemento <title>
                    String siteTitle = getElementTextContent("title", channelElement);

                    // Si no es vacio, lo meto como siteName del feed
                    if (!siteTitle.isEmpty()) {
                        feed.setSiteName(siteTitle);
                    }
                }
            } catch (Exception e) {
                System.err.println("No se pudo obtener el titulo del channel: " + e.getMessage());
            }
            
            // Obtengo una lista de nodos con todas las ocurrencias de la etiqueta <item> (los árticulos)
            NodeList itemList = doc.getElementsByTagName("item");
            
            // Itero sobre esa lista de nodos
            for (int i = 0; i < itemList.getLength(); i++) {

                // Obtengo el nodo i-écimo
                Node itemNode = itemList.item(i);
                // Me aseguro que el nodo sea un "tipo" elemento
                if (itemNode.getNodeType() == Node.ELEMENT_NODE) {

                    try {
                        // Si así es, lo parseo a Element
                        Element itemElement = (Element) itemNode;
                        
                        //Obtengo los hijos que necesito de <item>
                        String title = getElementTextContent("title", itemElement);
                        String description = getElementTextContent("description", itemElement);
                        String link = getElementTextContent("link", itemElement);

                         //Guardo la date como String pero la necesito como Date
                        String pubDateStr = getElementTextContent("pubDate", itemElement);
                        
                        Date pubDate = parseDate(pubDateStr);
                        
                        //Instancio el Article con los atributos que obtuve
                        Article article = new Article(title, description, pubDate, link);

                        //Instancio el Article con los atributos que obtuve
                        feed.addArticle(article);
                    } catch (Exception e) {
                        System.err.println("No se pudo procesar un articulo: " + e.getMessage());
                    }
                }
            }
        } catch (ParserConfigurationException e) {
            System.err.println("ERROR: No se pudo instanciar DocumentBuilder, " + e.getMessage());
            throw new RuntimeException("No se pudo instanciar una clase", e);
        } catch (IOException e) {
            System.err.println("ERROR: Ocurrió un problema I/O, " + e.getMessage());
            throw new RuntimeException("Problemas con un I/O", e);
        } catch (SAXException e) {
            System.err.println("ERROR: Ocurrió un error de parseo, " + e.getMessage());
            throw new RuntimeException("Problemas parseando", e);
        } catch (IllegalArgumentException e) { //NUNCA DEBERÍA LLEGAR ACÁ PERO LO PONGO POR COMPLETITUD
            System.err.println("ERROR: InputStream null, " + e.getMessage());
            throw new RuntimeException("El InputStream es null", e);
        }
        
        return feed;
    }

    /**
    * Método auxiliar para obtener el contenido de texto de la primera etiqueta hija
    * con un nombre específico, dentro de un elemento XML dado.
    * @param tagName  El nombre de la etiqueta hija a buscar (por ejemplo, "title").
    * @param element  El elemento padre en el que se busca la etiqueta hija (por ejemplo, el <channel>).
    * @return El texto contenido en la primera etiqueta hija con ese nombre, o una cadena vacía si no se encuentra.
 */
    private String getElementTextContent(String tagName, Element element) {
        try {
            // Busca todos los nodos hijos con ese nombre de etiqueta dentro del padre
            NodeList nodeList = element.getElementsByTagName(tagName);
            if (nodeList != null && nodeList.getLength() > 0) {
                 // Si encuentra al menos uno, devuelve el contenido de texto del primero
                Node node = nodeList.item(0);
                return nodeList.item(0).getTextContent();
            } else {
                // Si no encuentra ninguno, devuelve una cadena vacía para evitar errores de null
                return "";
            }
        } catch (Exception e) {
            System.err.println("Error al obtener valor de tag '" + tagName + " : " + e.getMessage());
        }
        return "";
    }

 /**
 * Método auxiliar para intentar convertir una cadena con una fecha en un objeto Date.
 * Usa un único formato fijo ("EEE, dd MMM yyyy HH:mm:ss z")
 *
 * @param pubDateStr La fecha como string.
 * @return Un objeto Date si el parseo fue exitoso, o null si falló.
 */
private Date parseDate(String pubDateStr) {
    // Instancio mi Date, si no la puedo parsear, queda en null
    Date publicationDate = null;

    try {
        // Le doy formato y Locale
        SimpleDateFormat dateFormat = new SimpleDateFormat("EEE, dd MMM yyyy HH:mm:ss z", Locale.ENGLISH);

        // Intento parsear solo si la cadena no está vacía
        if (pubDateStr != null && !pubDateStr.trim().isEmpty()) {
            publicationDate = dateFormat.parse(pubDateStr.trim());
        }

    } catch (NullPointerException e) {
        // Nunca debería llegar acá, a menos que el formato o el locale sea null (muy raro)
        System.err.println("ERROR: Patrón o Locale null en SimpleDateFormat, " + e.getMessage());

    } catch (IllegalArgumentException e) {
        // Esto sí puede pasar si el patrón del formato no es válido
        System.err.println("ERROR: Formato de fecha inválido, " + e.getMessage());

    } catch (ParseException e) {
        // La excepción más comun el texto no se puede convertir a fecha con este formato
        System.err.println("ADVERTENCIA: No se pudo parsear la fecha: " + pubDateStr + " | Error: " + e.getMessage());
    }

    // Si no se pudo parsear, queda como null
    return publicationDate;
}

}

/**
 * Hice una clase para poder manejar las excepciones de forma mas  personalizada para los errores de parseo
 */
class ParserException extends RuntimeException {
    public ParserException(String message, Throwable cause) {
        super(message, cause);
    }
}