//
// YodafyServidorIterativo
// (CC) jjramos, 2012
//
import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.Socket;
import java.net.UnknownHostException;

public class YodafyClienteUDP{

	public static void main(String[] args) {
		InetAddress direccion;
		DatagramPacket paquete;
		DatagramSocket socket;
		byte []buferEnvio;
		byte []buferRecepcion=new byte[256];
		int bytesLeidos=0;
		
		// Nombre del host donde se ejecuta el servidor:
		String host="localhost";
		// Puerto en el que espera el servidor:
		int port=8989;
		
		// Socket para la conexión TCP
		Socket socketServicio=null;
		
		try {
			// Creamos un socket que se conecte a "hist" y "port":
			System.out.println("Intentamos abrir el puerto...");
			socket = new DatagramSocket();
			direccion = InetAddress.getByName("localhost");
			buferEnvio="Al monte del volcán debes ir sin demora".getBytes();
			paquete = new DatagramPacket(buferEnvio, buferEnvio.length, direccion, port);
			System.out.println("El puerto ha sido abierto.");

			// Si queremos enviar una cadena de caracteres por un OutputStream, hay que pasarla primero a un array de bytes:
			
			// Enviamos el array por el outputStream;
			System.out.println("Los datos se están enviando.");
			socket.send(paquete);
			// Aunque le indiquemos a TCP que queremos enviar varios arrays de bytes, sólo
			// los enviará efectivamente cuando considere que tiene suficientes datos que enviar...
			// Podemos usar "flush()" para obligar a TCP a que no espere para hacer el envío:
			//outputStream.flush();
			System.out.println("Los datos han sido enviados.");
			
			// Leemos la respuesta del servidor. Para ello le pasamos un array de bytes, que intentará
			// rellenar. El método "read(...)" devolverá el número de bytes leídos.
			System.out.println("Estamos leyendo los datos procesados.");
			socket.receive(paquete);
			System.out.println("Los datos procesados han sido recibidos.");

			String palabra_recibida = new String(paquete.getData());
			System.out.println(palabra_recibida);
			
			// Una vez terminado el servicio, cerramos el socket (automáticamente se cierran
			// el inpuStream  y el outputStream)
			socket.close();
			
			// Excepciones:
		} catch (UnknownHostException e) {
			System.err.println("Error: Nombre de host no encontrado.");
		} catch (IOException e) {
			System.err.println("Error de entrada/salida al abrir el socket.");
		}
	}
}
