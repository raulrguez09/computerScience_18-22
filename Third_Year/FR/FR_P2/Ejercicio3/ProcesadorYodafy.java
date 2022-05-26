import java.io.BufferedReader;
import java.io.PrintWriter;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.net.Socket;
import java.util.Random;


public class ProcesadorYodafy {
    // Referencia a un socket para enviar/recibir las peticiones/respuestas
    private Socket socketServicio;
    // stream de lectura (por aquí se recibe lo que envía el cliente)
    private BufferedReader inReader;
    // stream de escritura (por aquí se envía los datos al cliente)
    private PrintWriter outPrinter;
    
    // Para que la respuesta sea siempre diferente, usamos un generador de números aleatorios.
    private Random random;
    
    // Constructor que tiene como parámetro una referencia al socket abierto en por otra clase
    public ProcesadorYodafy(Socket socketServicio) {
        this.socketServicio = socketServicio;
        random = new Random();
    }
    
    
    // Aquí es donde se realiza el procesamiento realmente:
    void procesa(){

        // Como máximo leeremos un bloque de 1024 bytes. Esto se puede modificar.
        System.out.println("Procedemos a leer los datos: ");
        String datosRecibidos;
        
        try {
            // Obtiene los flujos de escritura/lectura
            inReader = new BufferedReader(new InputStreamReader(socketServicio.getInputStream())); 
            outPrinter = new PrintWriter(socketServicio.getOutputStream(), true);
            
            // Lee la frase a Yodaficar:
            datosRecibidos = inReader.readLine();

            // Yoda reinterpreta el mensaje:
            String respuesta = yodaDo(datosRecibidos);
            
            // Enviamos la traducción de Yoda:
            outPrinter.println(respuesta);
        } catch (IOException e) {
            System.err.println("ERROR: Ocurrió un problema al obtener los flujos de entrada ysalida.");
        }

    }

    // Yoda interpreta una frase y la devuelve en su "dialecto":
    private String yodaDo(String peticion) {
        // Desordenamos las palabras:
        String[] s = peticion.split(" ");
        String resultado="";
        
        for(int i=0;i<s.length;i++){
            int j=random.nextInt(s.length);
            int k=random.nextInt(s.length);
            String tmp=s[j];
            
            s[j]=s[k];
            s[k]=tmp;
        }
        
        resultado=s[0];
        for(int i=1;i<s.length;i++){
          resultado+=" "+s[i];
      }

      return resultado;
  }
}
