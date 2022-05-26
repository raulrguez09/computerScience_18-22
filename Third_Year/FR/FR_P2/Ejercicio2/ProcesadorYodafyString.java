//
// YodafyServidorIterativo
// (CC) jjramos, 2012
//
import java.io.BufferedReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.io.InputStreamReader;
import java.net.Socket;
import java.util.Random;

//
// Nota: si esta clase extendiera la clase Thread, y el procesamiento lo hiciera el método "run()",
// ¡Podríamos realizar un procesado concurrente! 
//
public class ProcesadorYodafyString {
	// Referencia a un socket para enviar/recibir las peticiones/respuestas
	private Socket socketServicio;
	// Para que la respuesta sea siempre diferente, usamos un generador de números aleatorios.
	private Random random;
	
	// Constructor que tiene como parámetro una referencia al socket abierto en por otra clase
	public ProcesadorYodafyString(Socket socketServicio) {
		this.socketServicio=socketServicio;
		random=new Random();
	}
	
	
	// Aquí es donde se realiza el procesamiento realmente:
	void procesa(){
		String datosRecib = new String();
	
		System.out.println("Vamos a recibir datos...");

		try {
			// Obtiene los flujos de escritura/lectura
			BufferedReader inReader = new BufferedReader(new InputStreamReader(socketServicio.getInputStream()));
			PrintWriter outPrint = new PrintWriter(socketServicio.getOutputStream(), true);
			
			// Lee la frase a Yodaficar:
			datosRecib = inReader.readLine();
			System.out.println("Hemos recibido estos datos: " + datosRecib.length());
			System.out.println("Procedemos a procesar los datos que hemos recibido");
			
			// Yoda hace su magia:
			// Yoda reinterpreta el mensaje:
			String respuesta=yodaDo(datosRecib);
			System.out.println("LOs datos han sido procesados");
			System.out.println("Vamos a reenviarlos");
			
			// Enviamos la traducción de Yoda:
			outPrint.println(respuesta);
			System.out.println("Los datos han sido devueltos.");
			
			
			
		} catch (IOException e) {
			System.err.println("Error al obtener los flujos de entrada/salida.");
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
