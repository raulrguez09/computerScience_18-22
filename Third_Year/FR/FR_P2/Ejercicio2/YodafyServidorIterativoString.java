import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;

//
// YodafyServidorIterativo
// (CC) jjramos, 2012
//

public class YodafyServidorIterativoString {

	public static void main(String[] args) {
		// Puerto de escucha
		int port=8989;
		ServerSocket socketServidor;
		
		try {
			// Abrimos el socket en modo pasivo, escuchando el en puerto indicado por "port"
			System.out.println("Estamos intentando abrir el puerto.");
			socketServidor = new ServerSocket(port);
			System.out.println("El puerto ha sido abierto.");
			
			// Mientras ... siempre!
			do {
				System.out.println("Estamos escuchando.");
				// Aceptamos una nueva conexión con accept()
				Socket socketServicio = null;
				try {
					socketServicio = socketServidor.accept(); //Usar mas accept para atender mas peticiones
				} catch (IOException e) {
					System.out.println("ERROR: la conexion solicitada no ha sido aceptada.");
				}
				
				// Creamos un objeto de la clase ProcesadorYodafy, pasándole como 
				// argumento el nuevo socket, para que realice el procesamiento
				// Este esquema permite que se puedan usar hebras más fácilmente.
				ProcesadorYodafyString procesador=new ProcesadorYodafyString(socketServicio);
				procesador.procesa();
			} while (true);
			
		} catch (IOException e) {
			System.err.println("Error al escuchar en el puerto "+ port);
		}

	}

}