import java.io.IOException;
import java.net.DatagramSocket;
import java.net.DatagramPacket;

//
// YodafyServidorIterativo
// (CC) jjramos, 2012
//

public class YodafyServidorIterativo {

	public static void main(String[] args) {
		DatagramSocket socketServidor;
		DatagramPacket paquete;
		// Puerto de escucha
		int port=8989;
		// array de bytes auxiliar para recibir o enviar datos.
		byte []buffer=new byte[256];
		// Número de bytes leídos
		int bytesLeidos=0;
		
		try {
			// Abrimos el socket en modo pasivo, escuchando el en puerto indicado por "port"
			System.out.println("Estamos intentando abrir el puerto.");
			socketServidor = new DatagramSocket(port);
			paquete = new DatagramPacket(buffer, buffer.length);
			System.out.println("El puerto ha sido abierto.");
			
			// Mientras ... siempre!
			
			do {
				System.out.println("Estamos escuchando.");
				
				// Creamos un objeto de la clase ProcesadorYodafy, pasándole como 
				// argumento el nuevo socket, para que realice el procesamiento
				// Este esquema permite que se puedan usar hebras más fácilmente.
				ProcesadorYodafy procesador=new ProcesadorYodafy(socketServidor);
				procesador.procesa();
			} while (true);
			
		} catch (IOException e) {
			System.err.println("Error al escuchar en el puerto "+port);
		}

	}

}
