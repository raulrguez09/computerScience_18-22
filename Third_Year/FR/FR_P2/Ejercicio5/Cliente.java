import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.net.Socket;
import java.util.Scanner;
import java.io.PrintWriter;
import java.io.IOException;
import java.net.UnknownHostException;

public class Cliente {

    public static void main(String[] args){

        if(args.length != 2){

            System.out.println("Argumentos incorrectos, entrada de la forma: java Cliente <host> <puerto>");

        }else{

            String host = args[0]; 
            int puerto  = Integer.parseInt(args[1]); 

            String bufferEnvio; 
            String recibirBuffer; 
            Socket socketServicio = null;

            Scanner entrada = new Scanner(System.in); 
            boolean acertado = false; 
            
            try{
                
                socketServicio = new Socket(host, puerto);
                BufferedReader leerBuffer = new BufferedReader(new InputStreamReader(socketServicio.getInputStream()));
                PrintWriter escribirBuffer = new PrintWriter(socketServicio.getOutputStream(), true);
                
                String usuario, contra;
                int aux = 0;

                while(aux != 1 && aux != 2){

                    System.out.println("----------------------------------");
                    System.out.println("1: Login");
                    System.out.println("2: Registrarse\n");
                    System.out.print("SU OPCION: ");
                    aux = entrada.nextInt();
                    System.out.println("----------------------------------");

                    escribirBuffer.println(Integer.toString(aux));

                    if(aux != 1 && aux != 2){

                        System.out.println("Opcion incorrecta.");

                    }

                }

                boolean completado = false;


                while(completado == false){

                    System.out.print("Usuario: ");
                    usuario = entrada.next();
                    System.out.print("Contraseña: ");
                    contra = entrada.next();

                    escribirBuffer.println(usuario);
                    escribirBuffer.println(contra);

                    completado = Boolean.parseBoolean(leerBuffer.readLine());

                    if(completado == true){

                        System.out.println("\nOperacion realizada con exito\n");

                    }else{

                        System.out.println("\nNo se ha podido realizar la operacion\n");

                    }

                }
                
                recibirBuffer = leerBuffer.readLine();
                
                if(!recibirBuffer.equals("Limite")){ //Compruebo que están jugando los 4 jugadores y no más

                    int jugadorRecibido = Integer.parseInt(recibirBuffer); 

                    bufferEnvio = leerBuffer.readLine(); 
                    System.out.println(bufferEnvio); 

                    int turnoJugador;
                    boolean hayGanador;

                    while(acertado == false){ //Le preguntamos al jugador que le toque, cual cree que es la respuesta

                        turnoJugador = Integer.parseInt(leerBuffer.readLine());

                        if(jugadorRecibido == turnoJugador){ //Comprobamos que la hebra recibida es la que tiene el turno

                            System.out.print("¿Qué equipo crees que es?: ");
                            bufferEnvio = entrada.next();
                            
                            escribirBuffer.println(bufferEnvio);
                            recibirBuffer = leerBuffer.readLine();
                            
                            if(recibirBuffer.equals("Acierto")){ //Si ha acertado, mostramos por pantalla que gana y salimos del bucle

                                acertado = true;
                                System.out.println("----------------------------");
                                System.out.println("¡Has acertado el equipo!");
                                System.out.println("----------------------------");

                            }else if(recibirBuffer.equals("Perdedor")){ //En este caso se han agotado todas las pistas delos equipos y no se muestran más, aunque se sigue adivinando

                                System.out.println("----------------------------");
                                System.out.println("Has agotado todas las pistas");
                                System.out.println("----------------------------");

                            }else{ //Se muestra 1 pista sobre el equipo

                                System.out.println("----------------------------");
                                System.out.println("PISTA: " + recibirBuffer);
                                System.out.println("----------------------------");

                            }

                            hayGanador = Boolean.parseBoolean(leerBuffer.readLine());

                            if(hayGanador){ //Si hay un ganador, el juego termina para todos

                                int ganador = Integer.parseInt(leerBuffer.readLine());

                                System.out.println("-----------------------------------------");
                                System.out.println("Ha ganado jugador/a: " + (ganador + 1));
                                System.out.println("-----------------------------------------");
                                socketServicio.close();
                                acertado = true;

                            }

                        }else{ //Si la hebra recibida no tiene el turno, espera y actualiza

                            while(jugadorRecibido != turnoJugador){

                                try {

                                    Thread.sleep(1000);

                                }catch (Exception e) {}

                                turnoJugador = Integer.parseInt(leerBuffer.readLine());

                            }
                            
                        }
                        
                    }
                    
                    entrada.close();

                }else{ //Si se intenta unir cuando ya hay 4 jugadores, se le prohibe entrar

                    System.out.println("No se pueden unir más jugadores, ya hay 4");

                    entrada.close();
                    socketServicio.close();

                }

            }catch (UnknownHostException e){

                System.err.println("No se ha encontrado el host");

            }catch (IOException e){

                System.err.println("La entrada/salida del socket ha fallado");

            }catch (NumberFormatException e){
                
                System.err.println("Otro jugador ha acertado antes");

            }
        }
    }
}