//
// YodafyServidorIterativo
// (CC) jjramos, 2012
//
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;
import java.net.UnknownHostException;

public class YodafyClienteTCPString {

	public static void main(String[] args) {
		String buferEnvio;
		String buferRecepcion;
		
		// Nombre del host donde se ejecuta el servidor:
		String host="localhost";
		// Puerto en el que espera el servidor:
		int port=8989;
		
		// Socket para la conexión TCP
		Socket socketServicio=null;
		
		try {
			// Creamos un socket que se conecte a "hist" y "port":
			System.out.println("Vamos a intentar abrir el puerto.");
			socketServicio = new Socket(host, port);
			System.out.println("El puerto ha sido abierto.");
			
			System.out.println("Estamos estableciendo el flujo de datos.");
			BufferedReader inReader = new BufferedReader(new InputStreamReader(socketServicio.getInputStream()));
			PrintWriter outPrint = new PrintWriter(socketServicio.getOutputStream(), true);
			System.out.println("El flujo de datos ha sido establecido");

			// Si queremos enviar una cadena de caracteres por un OutputStream, hay que pasarla primero a un array de bytes:
			buferEnvio=new String("Al monte del volcan debes ir sin demora");
			
			// Enviamos el array por el outputStream;
			System.out.println("Estamos enviando los datos.");
			outPrint.println(buferEnvio);
			System.out.println("Los datos han sido enviados.");

			System.out.println("Procedemos a leer los datos procesados.");
			buferRecepcion = inReader.readLine();
			System.out.println("Datos procesados recibidos.");
			System.out.println("Hemos recibido " + buferRecepcion.length() + " bytes: ");

			System.out.println(buferRecepcion);

			socketServicio.close();
			
			// Excepciones:
		} catch (UnknownHostException e) {
			System.err.println("Error: Nombre de host no encontrado.");
		} catch (IOException e) {
			System.err.println("Error de entrada/salida al abrir el socket.");
		}
	}
}

