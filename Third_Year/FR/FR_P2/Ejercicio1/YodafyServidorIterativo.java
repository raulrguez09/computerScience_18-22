import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.ServerSocket;
import java.net.Socket;

//
// YodafyServidorIterativo
// (CC) jjramos, 2012
//
public class YodafyServidorIterativo {
	public static void main(String[] args) {
	
		// Puerto de escucha
		int port=8989;
		
		try {
			// Abrimos el socket en modo pasivo, escuchando el en puerto indicado por "port"
			System.out.println("Procedemos a abrir el puerto: ");
			ServerSocket socketServidor = new ServerSocket(port);
			System.out.println("Puerto abierto con éxito");
			
			// Mientras ... siempre!
			do {
				// Aceptamos una nueva conexión con accept()
				System.out.println("Buscando conexión: ");
				Socket socketServicio = null;
				
				try {
					socketServicio = socketServidor.accept(); 
				} catch (IOException e) {
					System.out.println("ERROR: ocurrió un problema al aceptar la conexion solicitada.");
				}
				
				// Creamos un objeto de la clase ProcesadorYodafy, pasándole como 
				// argumento el nuevo socket, para que realice el procesamiento
				// Este esquema permite que se puedan usar hebras más fácilmente.
				ProcesadorYodafy procesador=new ProcesadorYodafy(socketServicio);
				procesador.procesa();
				
			} while (true);
			
		} catch (IOException e) {
			System.err.println("Error al escuchar en el puerto "+port);
		}

	}

}
