import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.ServerSocket;
import java.net.Socket;

public class YodafyServidorConcurrente {

    public static void main(String[] args) {
        // Puerto de escucha
        int port = 8989;
        
        // Socket para el servidor
        ServerSocket socketServer;
        Socket socketServicio = null;
        
        try {
            socketServer = new ServerSocket(port);
            
            do {
                try {
                    HebraServidor h = new HebraServidor(socketServer.accept());
		    h.start();
                } catch (IOException e) {
                    System.out.println("Error: no se pudo aceptar la conexión solicitada.");
                }
            } while (true);
            
        } catch (IOException e) {
            System.err.println("Error al escuchar en el puerto "+port);
        }

    }

}

class HebraServidor extends Thread {
    private Socket socketServicio;

    HebraServidor(Socket socketServicio) {
	this.socketServicio = socketServicio;
    }

    public void run() {
	ProcesadorYodafy procesador=new ProcesadorYodafy(socketServicio);
	procesador.procesa();

	Thread.yield();
    }
}
