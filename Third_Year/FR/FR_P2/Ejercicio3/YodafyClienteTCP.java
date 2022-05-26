import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.net.Socket;
import java.net.UnknownHostException;

public class YodafyClienteTCP { 

    public static void main(String[] args) {
        // Nombre del host donde se ejecuta el servidor:
        String host = "localhost";
        // Puerto en el que espera el servidor:
        int port = 8989;

        int numClientes = args.length < 1 ? 1 : Integer.parseInt(args[0]);
                
        try {
            // Creamos un socket que se conecte a "host" y "port".
            for (int i = 0; i < numClientes; i++)
                (new ClienteHebra(new Socket(host, port))).start();
            
            
            // Excepciones:
        } catch (UnknownHostException e) {
            System.err.println("Error: Nombre de host no encontrado.");
        } catch (IOException e) {
            System.err.println("Error de entrada/salida al abrir el socket.");
        }
    }
}


class ClienteHebra extends Thread {
    private Socket socketServicio;

    ClienteHebra(Socket sk) {
        socketServicio = sk;
    }

    public void run() {
        try {
            String buferEnvio;
            String buferRecepcion;
            
            System.out.println("Procedemos a establecer el stream de datos: ");
            PrintWriter outPrinter = new PrintWriter(socketServicio.getOutputStream(), true);
            BufferedReader inReader = new BufferedReader(new InputStreamReader(socketServicio.getInputStream()));
            System.out.println("Stream de datos establecido con éxito \n");			

            // Enviamos el string por el outputStream
            System.out.println("Procedemos a enviar los datos: ");
			outPrinter.println("Al monte del volcan debes ir sin demora");
            System.out.println("Datos enviados con éxito \n");
            
            // Aunque le indiquemos a TCP que queremos enviar varios arrays de bytes, sólo
            // los enviará efectivamente cuando considere que tiene suficientes datos que enviar...
            // Podemos usar "flush()" para obligar a TCP a que no espere para hacer el envío:
            outPrinter.flush();

            // Mostremos la cadena de caracteres recibidos:
            System.out.println("Procedemos a leer los datos procesados: ");
			buferRecepcion = inReader.readLine();
			System.out.println("Datos procesados recibidos con éxito \n");
            
            System.out.println("Recibido: ");
            System.out.println(buferRecepcion);
            System.out.println("");
                       
            // Una vez terminado el servicio, cerramos el socket (automáticamente se cierran
            // el inputStream  y el outputStream)
            socketServicio.close();

            Thread.yield();
        } catch (IOException e) {
            System.err.println("Error de entrada/salida al abrir el socket.");
        }
    }
}