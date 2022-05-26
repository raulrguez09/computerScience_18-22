import java.net.Socket;
import java.net.ServerSocket;
import java.io.IOException;


public class Servidor{

    public static void main(String[] args){

        if(args.length != 1){ //Compruebo que se introduzca un puerto como argumento

            System.out.println("Argumentos incorrectos, entrada de la forma: java Servidor <puerto>");

        }else{ //Si se introduce correctamente

            ServerSocket socketServidor;
            int puerto = Integer.parseInt(args[0]);
            Jugadores jugador = Jugadores.getInstanceJuego();
            boolean acabado = false;

            try{ //Abro la conexion

                socketServidor = new ServerSocket(puerto);
                Socket socketaux = null;
                System.out.println("\nEste servidor esta escuchando el puerto: " + puerto + "\n");
                System.out.println("----------------------------------------------------");
                System.out.println("El equipo a adivinar es : " + jugador.getEquipoAdivinar().get(0));
                System.out.println("----------------------------------------------------");
                System.out.println("\nTienen que estar conectados todos los jugadores para empezar\n");

                while(acabado == false){

                    try{

                        socketaux = socketServidor.accept(); 

                    }catch (IOException e){

                        System.out.println("No se ha podido establecer la conexion.");

                    }
                    
                    Principal principal = new Principal(socketaux, jugador);
                    principal.start();

                }
                
            }catch(IOException e){

                System.err.println("Ha ocurrido un error escuchando el puerto: "+ puerto);

            }
        }
    }  
}