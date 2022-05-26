import java.util.ArrayList;
import java.util.Random;


public class Jugadores{

    private Random rand; 
    private ArrayList<String> equipoAdivinar;
    private static Jugadores instancia = null; 
    private int jugadorActual; 
    private static int numJugadores = 0; 

    private ArrayList<String> getEquipo(int n){ //Funcion donde se devuelven los datos del equipo que ha salido en un ArrayList

        ArrayList<String> devolver = new ArrayList<>();

        switch(n){
            case 0:

                devolver.add("R.Madrid");
                devolver.add("Es el equipo con mas Champions");
                devolver.add("Juega en España");
                devolver.add("Viste de blanco");

            break;

            case 1:

                devolver.add("Barcelona");
                devolver.add("Tiene al jugador con mas balones de oro");
                devolver.add("Juega en España");
                devolver.add("Viste de azul y rojo");

            break;

            case 2:

                devolver.add("Betis");
                devolver.add("Tiene a Joaquin");
                devolver.add("Su simbolo es la palmera");
                devolver.add("Viste de verde y blanco");

            break;
            
            case 3:
            	
            	devolver.add("Valencia");
                devolver.add("Regreso a 1ª division en la temporada 19/20");
                devolver.add("Su escudo tiene un murcielago");
                devolver.add("Su entrenador es Javi Gracia");
            
            break;

            case 4:
            	
            	devolver.add("Granada");
                devolver.add("Juega en 1ª division en la liga española");
                devolver.add("Su estadio se llama 'Estadio Nuevo Los Cármenes'");
                devolver.add("Su equipación titular es roji-blanca");
            
            break;
            
            case 5:
            	
            	devolver.add("Atletico");
                devolver.add("Su equipación titular es roji-blanca");
                devolver.add("Su estadio tiene una capacidad de 69 8294​ espectadores");
                devolver.add("El apodo de la aficion es 'colchoneros'");
            
            break;
            
            case 6:
            	
            	devolver.add("Athletic");
                devolver.add("Su equipación titular es roji-blanca");
                devolver.add("El tercer club español con mayor número de títulos oficiales");
                devolver.add("El apodo de la aficion son 'los leones'");
            
            break;
            
            case 7:
            	
            	devolver.add("Sevilla");
                devolver.add("El club se fundo el 25 de enero de 1890 ");
                devolver.add("Ha sido campeón de Liga una temporada y subcampeón cuatro veces");
                devolver.add("Su estadio es el Ramón Sánchez-Pizjuán");
            
            break;
            
            case 8:
            	
            	devolver.add("Español");
                devolver.add("Su equipación titular es blanqui-azul");
                devolver.add("El apodo de la aficion son 'los periquitos'");
                devolver.add("Descendio a 2ª division en la temporada 19/20");
            
            break;
            
            case 9:
            	
            	devolver.add("Villareal");
                devolver.add("Su equipación titular es amarilla");
                devolver.add("Su estadio es el Estadio de la Cerámica");
                devolver.add("Su entrenador es Unai Emery");
            
            break;
            
            case 10:
            	
            	devolver.add("Osasuna");
                devolver.add("Su equipación titular es roja");
                devolver.add("Su estadio es 'El Sadar'");
                devolver.add("Su entrenador es Jagoba Arrasate");
            
            break;

        }

        return devolver;

    }

    private Jugadores(){ //Constructor

        this.rand = new Random();
        this.equipoAdivinar = getEquipo(rand.nextInt(3));
        this.jugadorActual = 0;

    }

    public ArrayList<String> getEquipoAdivinar(){ //Devuelvelos datos del equipo a adivinar

        return this.equipoAdivinar;

    }

    public static int getNumJugadores(){ //Devuelve el numero de jugadores en determinado momento

        return numJugadores;

    }

    public int insertaJugadorActual(){ //Cuando añadimos un jugador, aumentamos el número de jugadores

        numJugadores++;
    
        return this.jugadorActual;

    }

    public int getJugadorActual(){ //Devuelve el jugador que está en el turno de adivinar.

        return jugadorActual;

    }

    public int getJugadoresMaximos(){ //Como hemos hecho el juego para 4 personas, devuelve siempre 4

        return 4;

    }

    public void cambiarTurno(){ //Cambiamos el jugador actual por el siguiente.

        jugadorActual = (getJugadorActual() + 1) % getJugadoresMaximos();

    }

    public static Jugadores getInstanceJuego(){ //Creamos la instancia del juego para ser llamada desde clases externas

		if(instancia == null){

            instancia = new Jugadores();
            
        }
        
        return instancia;
    }
}

