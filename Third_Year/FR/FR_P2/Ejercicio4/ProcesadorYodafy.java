//
// YodafyServidorIterativo
// (CC) jjramos, 2012
//
import java.io.IOException;
import java.net.DatagramPacket;
import java.net.InetAddress;
import java.net.DatagramSocket;
import java.util.Random;

//
// Nota: si esta clase extendiera la clase Thread, y el procesamiento lo hiciera el método "run()",
// ¡Podríamos realizar un procesado concurrente! 
//
public class ProcesadorYodafy {
	
	private DatagramSocket socketServicio;
	private DatagramPacket paquete;
	
	// Para que la respuesta sea siempre diferente, usamos un generador de números aleatorios.
	private Random random;
	
	// Constructor que tiene como parámetro una referencia al socket abierto en por otra clase
	public ProcesadorYodafy(DatagramSocket socketServicio) {
		this.socketServicio=socketServicio;
		random=new Random();
	}
	
	
	// Aquí es donde se realiza el procesamiento realmente:
	void procesa(){
		// Como máximo leeremos un bloque de 1024 bytes. Esto se puede modificar.
		byte [] datosRecibidos=new byte[1024];
		int bytesRecibidos=0;
		// Array de bytes para enviar la respuesta. Podemos reservar memoria cuando vayamos a enviarla:
		byte [] datosEnviar;

		paquete = new DatagramPacket(datosRecibidos, datosRecibidos.length);

		System.out.println("Los datos van a ser recibidos.");

		try {
			// Aquí obtenemos el paquete
			socketServicio.receive(paquete);
			
			// Lee la frase a Yodaficar:
			String peticion = new String(datosRecibidos);
			System.out.println("Los datos recibidos son: " + peticion);
			System.out.println("Nos disponemos a procesar los datos recibidos.");
			
			// Yoda hace su magia:
			// Yoda reinterpreta el mensaje:
			String respuesta=yodaDo(peticion);
			// Convertimos el String de respuesta en una array de bytes:
			datosEnviar=respuesta.getBytes();
		
			// Enviamos la traducción de Yoda:
			InetAddress direccionRetorno = paquete.getAddress();
			int puerto = paquete.getPort();
			paquete = new DatagramPacket(datosEnviar, datosEnviar.length, direccionRetorno, puerto);
			socketServicio.send(paquete);
			System.out.println("Datos devueltos.");
			
			
			
		} catch (IOException e) {
			System.err.println("Error al obtener los flujaso de entrada/salida.");
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
