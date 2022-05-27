package abafar;

//------------------------------------------------------------------------------------------------------------
// Desarrollo basado en Agentes
// Práctica 2: Find the lost jedi
//
// Equipo: 103 Corps
// Alumnos: Agustin Merida Gutierrez
//          Ruben Delgado Pareja
//          Ángel Gómez Ferrer
//          Raúl Rodríguez Pérez
//
// Curso: 21/22
// Especialidad de ingeniería del software
// @author comentarios: Raúl Rodríguez Pérez
//------------------------------------------------------------------------------------------------------------

import agents.LARVAFirstAgent;
import jade.core.AID;
import jade.lang.acl.ACLMessage;
import static java.lang.Math.abs;
import java.util.*;
import swing.LARVADash;

public class MyFirstAbafar extends LARVAFirstAgent{
    // Estados que representan el ciclo de vida del Agente
    enum Status {
        CHECKIN, CHECKOUT, OPENPROBLEM, COMISSIONING, JOINSESSION, SOLVEPROBLEM, CLOSEPROBLEM, EXIT
    }
    Status mystatus;

    // Array de los mundos a completar para la práctica 2
    String[] mundos = {"Abafar", "Batuu","Chandrila","Dathomir", "Endor", "Felucia", "Hoth", "Mandalore", "Tatooine", "Wobani", "Zeffo"};
    
    String service = "PManager", 
           problem = mundos[4],             // Problema o mundo elegido para la ejecución
           problemManager = "",             // Almacenamos quien es el PManager de la sesión
           content, 
           sessionKey,                      // Clave de la sessión 
           sessionManager,                  // Almacenamos quien es el sessionManager de la sesión
           storeManager,                    // Agente que contiene los sensores para la tieFighter
           sensorKeys;                      // Almacena las claves de los sensores que nos da el store


    int width,                              // Ancho del mundo
        height,                             // Altura del mundo
        maxFlight;                          // Altura máx permitida para volar con la tieFighter

    double gps[];
    double angular, compass;

    // Variables para memoria
    double[] casillas_x = new double[50];
    double[] casillas_y = new double[50];

    // Variables para comprobar casillas rep
    boolean casilla_repe = false;
    double siguiente_x;
    double siguiente_y;
    int it = 0;
    int visual[][] ;
    boolean choca = false;
    boolean calcular_giro = false;
    String giro = "LEFT";

    
    ACLMessage open, session;
    String[] contentTokens, 
    mySensors = new String[] {
        "ALIVE",                            // Define si el agente esta vivo o no
        "ONTARGET",                         // Define si el agente esta o no en la posición exacta del objetivo
        "GPS",                              // Define la posición del agente en un eje de cordenadas (x,y,z)    
        "COMPASS",                          // Define el valor que indica la orientación del agente
        //"LIDAR",                          // Define la distancia del agente con respecto del suelo (malla 11x1)
        "ALTITUDE",                         // Define la altura a la que se encuentra el agente sobre el suelo
        "VISUAL",                           // Define una malla 11x11 con el valor que indica la elevación del suelo alrededor del agente
        "ENERGY",                           // Define la energía que dispone el agente para realizar acciones
        //"PAYLOAD",                        // Define el número de objetos recogidos en la bodega
        "DISTANCE",                         // Define la distancia a la que se encuentra el jedi sin tener en cuenta la orientación
        "ANGULAR",                          // Define el ángulo en el que se encuentra el jedi
        //"THERMAL"                         // Define una malla 11x11 con el valor que indica el calor que desprende los objetos alrededor del agente
    };
    boolean step = false;

    //------------------------------------------------------------------------------------------------------------
    // Función que realiza la configuración e inicialización del agente
    //------------------------------------------------------------------------------------------------------------
    @Override
    public void setup() {
        super.setup();
        logger.onOverwrite();
        logger.setLoggerFileName("mylog.json");
        //this.enableDeepLARVAMonitoring();
        Info("Setup and configure agent");
        mystatus = Status.CHECKIN;
        exit = false;
        this.myDashboard = new LARVADash(this);
        this.doActivateLARVADash();
    }

    //------------------------------------------------------------------------------------------------------------
    // Cuerpo principal del ciclo de vida
    // Función que ejecuta paso a paso o del tirón, todos los estados que conforman el ciclo de vida del agente
    // Termina cuando la variable exit == true, en caso contrario se repite de nuevo
    //------------------------------------------------------------------------------------------------------------
    @Override
    public void Execute() {
        Info("Status: " + mystatus.name());
        if (step) {
            step = this.Confirm("The next status will be " + mystatus.name() + "\n\nWould you like to continue step by step?");
        }
        switch (mystatus) {
            case CHECKIN:
                mystatus = MyCheckin();
                break;
            case OPENPROBLEM:
                mystatus = MyOpenProblem();
                break;
            case COMISSIONING:
                mystatus = MyComissioning();
                break;
            case JOINSESSION:
                mystatus = MyJoinSession();
                break;
            case SOLVEPROBLEM:
                mystatus = MySolveProblem();
                break;
            case CLOSEPROBLEM:
                mystatus = MyCloseProblem();
                break;
            case CHECKOUT:
                mystatus = MyCheckout();
                break;
            case EXIT:
            default:
                exit = true;
                break;
        }
    }

    //------------------------------------------------------------------------------------------------------------
    // Función que realiza el cierre y la borrado del agente
    //------------------------------------------------------------------------------------------------------------    
    @Override
    public void takeDown() {
        Info("Taking down and deleting agent");
        this.saveSequenceDiagram("./" + this.problem + ".seqd");
        super.takeDown();
    }

    //------------------------------------------------------------------------------------------------------------
    // Función para registrar al agente en Larva con el uso del passport
    //------------------------------------------------------------------------------------------------------------    
    public Status MyCheckin() {
        Info("Loading passport and checking-in to LARVA");
        if (!loadMyPassport("passport/MyPassport.passport")) {
            Error("Unable to load passport file");
            return Status.EXIT;
        }
        if (!doLARVACheckin()) {
            Error("Unable to checkin");
            return Status.EXIT;
        }
        return Status.OPENPROBLEM;
    }

    //------------------------------------------------------------------------------------------------------------
    // Función para abrir la instancia de un problema por medio del PManager
    // El PManager nos asignará un SessioneManager durante todo el problema
    //------------------------------------------------------------------------------------------------------------
    public Status MyOpenProblem() {
        if (this.DFGetAllProvidersOf(service).isEmpty()) {
            Error("Service PMANAGER is down");
            return Status.CHECKOUT;
        }
        
        for(int i=0; i < 50; i++){
           this.casillas_x[i]= this.casillas_y[i] = -1; 
        }
        
        
        problemManager = this.DFGetAllProvidersOf(service).get(0);
        Info("Found problem manager " + problemManager);
        this.outbox = new ACLMessage();
        outbox.setSender(getAID());
        outbox.addReceiver(new AID(problemManager, AID.ISLOCALNAME));
        outbox.setContent("Request open " + problem);
        this.LARVAsend(outbox);
        Info("Request opening problem " + problem + " to " + problemManager);
        open = LARVAblockingReceive();
        Info(problemManager + " says: " + open.getContent());
        content = open.getContent();
        contentTokens = content.split(" ");
        if (contentTokens[0].toUpperCase().equals("AGREE")) {
            sessionKey = contentTokens[4];
            session = LARVAblockingReceive();
            sessionManager = session.getSender().getLocalName();
            Info(sessionManager + " says: " + session.getContent());
            return Status.COMISSIONING;
        } else {
            Error(content);
            return Status.CHECKOUT;
        }
        
        
    }

  
    //------------------------------------------------------------------------------------------------------------
    // Función para cerrar la instancia de un problema
    //------------------------------------------------------------------------------------------------------------
    public Status MyCloseProblem() {
        outbox = open.createReply();
        outbox.setContent("Cancel session " + sessionKey);
        Info("Closing problem Helloworld, session " + sessionKey);
        this.LARVAsend(outbox);
        inbox = LARVAblockingReceive();
        Info(problemManager + " says: " + inbox.getContent());
        return Status.CHECKOUT;
    }

    //------------------------------------------------------------------------------------------------------------
    // Función para que el agente abandone la sesión en Larva 
    //------------------------------------------------------------------------------------------------------------
    public Status MyCheckout() {
        this.doLARVACheckout();
        return Status.EXIT;
    }

    //------------------------------------------------------------------------------------------------------------
    // Función para consultar acerca del storeManager y almacenar todos los sensorKeys de los sensores que 
    // vamos a emplear para la resolución del problema
    //------------------------------------------------------------------------------------------------------------
    public Status MyComissioning() {
        String localService ="STORE "+sessionKey;
        if(this.DFGetAllProvidersOf(localService).isEmpty()) {
            Error("Service STORE is down");
            return Status.CLOSEPROBLEM;
        }
        storeManager = this.DFGetAllProvidersOf(localService).get(0);
        Info("Found store manager "+ storeManager);
        sensorKeys = "";
        for(String s: mySensors){
            outbox = new ACLMessage();
            outbox.setSender(this.getAID());
            outbox.addReceiver(new AID(storeManager, AID.ISLOCALNAME));
            outbox.setContent("Request product "+s+" session "+sessionKey);
            this.LARVAsend(outbox);
            inbox = this.LARVAblockingReceive();
            if(inbox.getContent().startsWith("Confirm")){
                Info("Bought sensor "+s);
                sensorKeys += inbox.getContent().split(" ")[2]+" ";
            } else {
                this.Alert("Sensor "+s+" could not be obtained");
                return Status.CLOSEPROBLEM;
            }
        }
        Info("Bought all sensor keys "+sensorKeys);
        return Status.JOINSESSION;
    }

    //------------------------------------------------------------------------------------------------------------
    // Función para iniciar sesión en el problema, entrando en el mundo con los sensores que hemos adquirido
    //------------------------------------------------------------------------------------------------------------
    public Status MyJoinSession() {
        session = session.createReply();
        session.setContent("Request join session "+sessionKey+" attach sensors "+sensorKeys);
        this.LARVAsend(session);
        session = this.LARVAblockingReceive();
        String parse[] = session.getContent().split(" ");
        if(parse[0].equals("Confirm")){
            width = Integer.parseInt(parse[8]);
            height = Integer.parseInt(parse[10]);
            maxFlight = Integer.parseInt(parse[14]);
        }
        else{
            Alert("Error joining session: "+session.getContent());
            return Status.CLOSEPROBLEM;
        }
        
        
        return Status.SOLVEPROBLEM;
        
    }

    //------------------------------------------------------------------------------------------------------------
    // Función que muestra el estado de todos los sensores empleados en la resolución del problema
    // @author: Ruben Delgado Pareja, Agustin Merida Gutierrez, Raúl Rodríguez Pérez
    //------------------------------------------------------------------------------------------------------------
    public void Sensors(){
        // Leer los valores actuales de los sensores
        session = session.createReply();
        session.setContent("Query sensors session "+sessionKey);
        this.LARVAsend(session);
        session = this.LARVAblockingReceive();
        
        // Si la lectura de los sensores falla, lo notificamos
        if( session.getContent().startsWith("Refuse") || session.getContent().startsWith("Failure")){
            Alert("Reading of sensors failed due to "+session.getContent());
        }

        // Almacenamos los valores de los sensores usando el Dashboard
        this.gps = myDashboard.getGPS();
        this.angular = myDashboard.getAngular();
        this.compass = myDashboard.getCompass();
        double distance = myDashboard.getDistance();
        this.visual = myDashboard.getVisual();

        // Mostramos por terminal las lecturas de todos los sensores
        Info("Reading of GPS\nX="+ this.gps[0] +" Y="+ this.gps[1] +" Z=" +this.gps[2]);
        Info("Reading of compass="+ this.compass +"º");
        Info("Reading of angular= "+ this.angular +"º");
        Info("Reading of altura="+ myDashboard.getAltitude() +" de distancia");
        Info("Reading of distance= "+ distance +"m");
        String message="Reading of sensor Visual;\n"; 
        for(int y=0; y<this.visual.length; y++){
            for(int x=0; x<this.visual[0].length; x++){
                message += String.format("%03d ", this.visual[y][x]);
            }
            message += "\n";
        }
        Info(message);
    }

    //------------------------------------------------------------------------------------------------------------
    // Función donde se ejecutan las acciones para resolver los mundos/problemas
    // @author: Ruben Delgado Pareja, Agustin Merida Gutierrez, Raúl Rodríguez Pérez
    //------------------------------------------------------------------------------------------------------------
    public Status MySolveProblem() {
        
        this.cambiar_giro();
            
            // Milestone: "Execute actions that are planned to happen every certain periods of time"
            // Realizamos una recarga cada cierto periodo de tiempo, aunque esta no se realice debido a
            // que no estamos en el suelo  
            if( myDashboard.getTimerSecs()%10 == 0){
                this.doAction("RECHARGE");
                if( session.getContent().startsWith("Refuse") || session.getContent().startsWith("Failure")){
                    Alert("Reading of action failed due to "+session.getContent());
                    return Status.CLOSEPROBLEM;
                }
            }
            
            // Si nuestra distancia con el objetivo no es 0
            if(myDashboard.getDistance() != 0){
                // Comprobamos si tenemos que cambiar la orientación de la tieFighter
                if( this.angular != this.compass && abs(this.angular - this.compass) >= 45  && abs(this.angular - this.compass) < 315 && !this.choca ){
                    // Si tenemos que modificarla, realizamos el giro
                    this.turnTF();
                    if( session.getContent().startsWith("Refuse") || session.getContent().startsWith("Failure")){
                        Alert("Reading of action failed due to "+session.getContent());
                        return Status.CLOSEPROBLEM;
                    }
                } else {
                    // Si tenemos la tieFighter orientada correctamente
                    // Calculamos la altura de la casilla a donde nos queremos desplazar
                    this.height = this.calculateNextHeight();

                    // Si la altura de la siguiente casilla es superior a la altura max del mapa 
                    // o la casilla está repetida
                    if( (this.height > maxFlight) || this.casilla_repe ){
                        // Realizamos el giro dependiendo de la heurística que estemos siguiendo (left/right wall)
                        this.doAction(giro);
                        if( session.getContent().startsWith("Refuse") || session.getContent().startsWith("Failure")){
                            Alert("Reading of action failed due to "+session.getContent());
                            return Status.CLOSEPROBLEM;
                        }
                        this.choca = true;
                    }else{
                        // Si la altura de la casilla es superior a nuestra altura actual
                        if( this.height > this.gps[2]  ){
                            Info("Valor de mi pos_x: "+myDashboard.getGPS()[0]);
                            Info("Valor de mi pos_y: "+myDashboard.getGPS()[1]);
                            Info("Valor de mi altura: "+myDashboard.getGPS()[2]);
                            Info("valor de la altura de la siguiente casilla "+ this.height);

                            // Volamos para poder superar la altura de la prox casilla 
                            this.doAction("UP");
                            if( session.getContent().startsWith("Refuse") || session.getContent().startsWith("Failure")){
                                Alert("Reading of action failed due to "+session.getContent());
                                return Status.CLOSEPROBLEM;
                            }
                        }else if(this.height >= 0){
                            Info("Valor de mi altura"+ myDashboard.getGPS()[2]);
                            Info("valor de la altura de la siguiente casilla "+ this.height);

                            // Si la altura de la prox casilla es igual o mayor que 0 (no chocarse con los límites)
                            // Nos movemos a la prox casilla
                            this.doAction("MOVE");
                            if( session.getContent().startsWith("Refuse") || session.getContent().startsWith("Failure")){
                                Alert("Reading of action failed due to "+session.getContent());
                                return Status.CLOSEPROBLEM;
                            }
                            
                            this.Sensors();
                            // Se guardan las casillas cada vez que hacemos un move
                            this.casillas_x[this.it%50] = this.gps[0];
                            this.casillas_y[this.it%50] = this.gps[1];
                            this.it++;
                        } 
                        this.choca = false;
                    }
                }
                
            }else {
                    // Si nuestra distancia es 0, nos encontramos en la casilla objetivo
                    // Bajamos la nave para rescatar al jedi
                    this.doAction("DOWN");
                    if( session.getContent().startsWith("Refuse") || session.getContent().startsWith("Failure")){
                        Alert("Reading of action failed due to "+session.getContent());
                        return Status.CLOSEPROBLEM;
                    }
                    this.Sensors();
                    
            }
            
            // Comprobamos nuestra energía disponible y la altitud a la que estamos
            // Y si necesitamos recargar bajamos a tierra para hacerlo
            this.rechargeTF();
            if( session.getContent().startsWith("Refuse") || session.getContent().startsWith("Failure")){
                Alert("Reading of action failed due to "+session.getContent());
                return Status.CLOSEPROBLEM;
            }
        
        // Si hemos llegado al objetivo, solo queda capturar al jedi
        if(myDashboard.getOnTarget() == true){
            this.doAction("CAPTURE");
            if( session.getContent().startsWith("Refuse") || session.getContent().startsWith("Failure")){
                Alert("Reading of action failed due to "+session.getContent());
                return Status.CLOSEPROBLEM;
            }
            
            return Status.CLOSEPROBLEM;    
        }
        
        this.casilla_repe = false;
        
        return Status.SOLVEPROBLEM;
         
    }

    //------------------------------------------------------------------------------------------------------------
    // Función que permite al tieFighter, realizar la acción pasada por parámetro
    // @author: Ruben Delgado Pareja, Agustin Merida Gutierrez
    //------------------------------------------------------------------------------------------------------------
    public void doAction(String action) {
        session = session.createReply();
        session.setContent("Request execute " + action + " session "+sessionKey);
        this.LARVAsend(session);
        session = this.LARVAblockingReceive();
    }
    
    //------------------------------------------------------------------------------------------------------------
    // Función que comprueba y establece cuando debe realizar cambios en la orientación de la tieFighter
    // @author: Ruben Delgado Pareja, Agustin Merida Gutierrez, Raúl Rodríguez Pérez
    //------------------------------------------------------------------------------------------------------------
    public void turnTF() {
        // Si el ángulo de la nave es inferior al ángulo al que se encuentra el objetivo
        if( this.compass < this.angular ){
            // Comprobamos si debemos movernos a la dcha o a la izda
            if( (this.angular-180) > this.compass ){
                    this.doAction("RIGHT");
                    this.Sensors(); 
            }else{
                    this.doAction("LEFT");
                    this.Sensors(); 
            }

        }else if( this.compass > this.angular ){
            // Si el ángulo de la nave es mayor al ángulo al que se encuentra el objetivo
            // Comprobamos si debemos movernos a la dcha o a la izda
            if( (this.compass - 180) > this.angular ){
                    this.doAction("LEFT");
                    this.Sensors(); 
            }else {
                    this.doAction("RIGHT");
                    this.Sensors(); 
            }
        }
    }

    //------------------------------------------------------------------------------------------------------------
    // Función que calcula la altura de la prox casilla, dependiendo de la orientación de la tieFighter
    // @author: Ruben Delgado Pareja, Agustin Merida Gutierrez, Raúl Rodríguez Pérez
    //------------------------------------------------------------------------------------------------------------
    public double calculateNextHeight() {
        double res = 0;
        this.Sensors();
        
        // Comprobamos si debemos alternar el giro de dcha a izda o viceversa
        if( this.visual[5][5+1] < maxFlight &&  this.visual[5-1][5+1] < maxFlight &&  this.visual[5-1][5] < maxFlight 
             &&  this.visual[5-1][5-1] < maxFlight && this.visual[5][5-1] < maxFlight && this.visual[5+1][5-1] < maxFlight 
             &&  this.visual[5+1][5] < maxFlight && this.visual[5+1][5+1] < maxFlight
             &&  this.visual[3][3] < maxFlight &&  this.visual[3][4] < maxFlight &&  this.visual[3][5] < maxFlight  &&  this.visual[3][6] < maxFlight &&  this.visual[3][7] < maxFlight
             &&  this.visual[4][3] < maxFlight &&  this.visual[4][7] < maxFlight &&  this.visual[5][3] < maxFlight  &&  this.visual[5][7] < maxFlight &&  this.visual[6][3] < maxFlight
             &&  this.visual[6][7] < maxFlight&&  this.visual[7][3] < maxFlight && this.visual[7][4] < maxFlight &&  this.visual[7][5] < maxFlight &&  this.visual[7][6] < maxFlight
                 &&  this.visual[7][7] < maxFlight
             
             ){
            this.calcular_giro = true;
        }else{
            this.calcular_giro = false;
        }
        
        // Dependiendo de la orientación de la tieFighter
        // seleccionaremos la altura de una casilla distinta, de entre las que se encuentran alrededor de la nave
        // además añadiremos dicha casilla en memoria
        switch ( (int) myDashboard.getCompass() ){
            case 0:
                res = this.visual[5][5+1];
                this.siguiente_x = this.gps[0]+1;
                this.siguiente_y = this.gps[1];
                 Info("Altura de la siguiente casilla: "+ this.height);
                break;
            case 45:
                res = this.visual[5-1][5+1];
                this.siguiente_x = this.gps[0]+1;
                this.siguiente_y = this.gps[1]-1;
                Info("Altura de la siguiente casilla: "+ this.height);
                break;
            case 90:
                res = this.visual[5-1][5];
                this.siguiente_x = this.gps[0];
                this.siguiente_y = this.gps[1]-1;
                Info("Altura de la siguiente casilla: "+ this.height);
                break;
            case 135:
                res = this.visual[5-1][5-1];
                this.siguiente_x = this.gps[0]-1;
                this.siguiente_y = this.gps[1]-1;
                Info("Altura de la siguiente casilla: "+ this.height);
                break;
            case 180:
                res = this.visual[5][5-1];
                this.siguiente_x = this.gps[0]-1;
                this.siguiente_y = this.gps[1];
                Info("Altura de la siguiente casilla: "+ this.height);
                break;
            case 225:
                res = this.visual[5+1][5-1];
                this.siguiente_x = this.gps[0]-1;
                this.siguiente_y = this.gps[1]+1;
                Info("Altura de la siguiente casilla: "+ this.height);
                break; 
            case 270:
                res = this.visual[5+1][5];
                this.siguiente_x = this.gps[0];
                this.siguiente_y = this.gps[1]+1;
                Info("Altura de la siguiente casilla: "+ this.height);
                break;
            case 315:
                res = this.visual[5+1][5+1];
                this.siguiente_x = this.gps[0]+1;
                this.siguiente_y = this.gps[1]+1;
                Info("Altura de la siguiente casilla: "+ this.height);
                break;
            default:
                Alert("ERROR");
                break;
        }
        
        // Comprobar si la casilla a la que vamos a ir es repetida o no
        for(int i=0; i < 50; i++){
            if( this.casillas_x[i] == this.siguiente_x && this.casillas_y[i] == this.siguiente_y){
                this.casilla_repe = true;
            }
        }
        
        return res;
    }
    
    //------------------------------------------------------------------------------------------------------------
    // Función que establece qué debemos hacer y cuando debemos recargar la tieFighter
    // @author: Ruben Delgado Pareja, Agustin Merida Gutierrez
    //------------------------------------------------------------------------------------------------------------
    public void rechargeTF() {
        // Si la eneergía es inferior a 1000 W
        if( myDashboard.getEnergy() < 1000 ){
            
            // Bajamos hasta que llegemos al suelo
            while(myDashboard.getAltitude() > 0){
                this.doAction("DOWN");
                this.Sensors();
            }

            // Recargamos una vez estemos en tierra
            this.doAction("RECHARGE");
        }
    }

    //------------------------------------------------------------------------------------------------------------
    // Función que alterna entre girar izda o dcha según los valores de los sensores
    // @author: Ruben Delgado Pareja
    //------------------------------------------------------------------------------------------------------------
    public void cambiar_giro(){
        if( this.calcular_giro ){
                if( this.compass < this.angular ){
                    if( (this.angular-180) > this.compass ){
                        giro = "RIGHT";
                    }else{
                        giro = "LEFT";
                    }
                }else if( this.compass > this.angular ){
                    if( (this.compass - 180) > this.angular ){
                            giro = "LEFT";
                    }else {
                            giro = "RIGHT";
                    }
                }
            }
        }
    
}