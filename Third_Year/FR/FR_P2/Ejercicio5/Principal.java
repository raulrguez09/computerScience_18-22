import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;
import java.io.IOException;


public class Principal extends Thread{

    private Socket socketServicio; 
    Jugadores juego; 
    LoginRegister loginregister;
 
    static boolean terminado = false;
    static int jugadoresConect = 0;
    int jugadorActual;
    static int jugadorTurno = 0;
    static int jugadorGanador;
    int contadorFallos = 0;

    public Principal(Socket socketServicio, Jugadores juego){

        this.socketServicio = socketServicio;
        this.juego = Jugadores.getInstanceJuego();
        this.loginregister = new LoginRegister();

    }

    public static int getjugadorTurno(){

        return jugadorTurno;

    }

    public static int getJugadoresConect(){

        return jugadoresConect;

    }

    @Override
    public void run(){
        
        String equipoRecibido;
        int aux = 0;
        
        try{

            BufferedReader leerBuffer = new BufferedReader(new InputStreamReader(socketServicio.getInputStream()));
            PrintWriter escribirBuffer = new PrintWriter(socketServicio.getOutputStream(), true);
            
            while(aux != 1 && aux != 2){

                aux = Integer.parseInt(leerBuffer.readLine()); 

            }

            String usuario= " ";
            String contra = " ";
            boolean completado = false;

            while(completado == false){ //El cliente me pasa el usuario, la contraseña, y si desea registrar o loggear

                usuario = leerBuffer.readLine();
                contra = leerBuffer.readLine();

                if(aux == 1){

                    completado = loginregister.login(usuario, contra);

                }else{

                    completado = loginregister.register(usuario, contra);

                }

                escribirBuffer.println(completado);

            }

            if(Jugadores.getNumJugadores() < juego.getJugadoresMaximos()){ //Mientras la partida no esté llena, meto usuarios y lo aviso en el servidor

                System.out.println(usuario + " eres el jugador numero " + juego.insertaJugadorActual());
                escribirBuffer.println(Integer.toString(juego.getJugadorActual()));
                juego.cambiarTurno();

            }else{ //Si la partida ya está llena, lo aviso y mando una señal al cliente

                System.out.println("PARTIDA LLENA");
                escribirBuffer.println("Limite");
                socketServicio.close();

            }

            jugadoresConect++; 
            jugadorActual = jugadoresConect; 
            jugadorActual--;  
            setName(Integer.toString(jugadorActual));

            while(jugadoresConect != juego.getJugadoresMaximos()){ //Esperamos hasta que estén todos los jugadores

                try{

                    Thread.sleep(1000);

                }catch (Exception e) {}

                jugadoresConect = Principal.getJugadoresConect();

            }

            if(getName().equals("1")){ //Digo por el servidor que los jugadores están

                System.out.println("La partida puede comenzar");

            }

            escribirBuffer.println("La partida va a comenzar"); //Esto se lo digo a los clientes

            do{
                
                escribirBuffer.println(Integer.toString(jugadorTurno));

                if(jugadorTurno == jugadorActual){ //Si es el turno del jugador
                    
                    equipoRecibido = leerBuffer.readLine(); 

                    if(equipoRecibido.equals(juego.getEquipoAdivinar().get(0))){ //Si su prediccion es correcta, hemos acabado

                        escribirBuffer.println("Acierto");
                        System.out.println("Fin del juego");

                        terminado = true;
                        jugadorGanador = jugadorActual;

                    }else if(contadorFallos < 3){ //Cada equipo tiene 3 pistas, en cada iteracion se muestra una distinta

                        escribirBuffer.println(juego.getEquipoAdivinar().get(contadorFallos + 1));
                        contadorFallos++;

                    }else{ //Si nos quedmaos sin pistas, le decimos al cliente que ya no hay más

                        escribirBuffer.println("Perdedor");

                    }

                    escribirBuffer.println(terminado); 

                    if(terminado){ //Envio el jugador que ha ganado

                        escribirBuffer.println(Integer.toString(jugadorGanador));

                    }

                    jugadorTurno = (jugadorTurno + 1) % Jugadores.getNumJugadores();

                }else{ //SI no es el turno, se espera

                    while(jugadorActual != jugadorTurno){

                        try {
                            Thread.sleep(1000);
                        } catch (Exception e) {}
                        jugadorTurno = Principal.getjugadorTurno();
                        escribirBuffer.println(Integer.toString(jugadorTurno));
                        if(terminado){
                            socketServicio.close();
                        }

                    }

                }
                
            }while(terminado != true);
                
                socketServicio.close();
                
            } catch (IOException e) {
                System.err.println("Error al obtener los flujso de entrada/salida.");
            }
    }

}