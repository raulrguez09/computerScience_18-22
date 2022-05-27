package practica3;

//------------------------------------------------------------------------------------------------------------
// Desarrollo basado en Agentes
// Práctica 3: Clone Protocol 66
//
// Equipo: 103 Corps
// Alumnos: Agustin Merida Gutierrez
//          Ruben Delgado Pareja
//          Ángel Gómez Ferrer
//          Raúl Rodríguez Pérez
//
// Curso: 21/22
// Especialidad de ingeniería del software
// @author comentarios: Ángel Gómez Ferrer y Raúl Rodríguez Pérez
// @author código: Todos hemos participado en la creación de los distintos métodos.
//------------------------------------------------------------------------------------------------------------

import agents.LARVAFirstAgent;
import geometry.Point;
import jade.core.AID;
import jade.lang.acl.ACLMessage;
import jade.lang.acl.MessageTemplate;
import static java.lang.Math.abs;
import java.util.*;
import swing.LARVADash;
import java.util.Random;

//CODIGO CORELLIAN
public class Corellian extends LARVAFirstAgent{
    //Posibles estados del Corellian para definir su ejecución
    enum Status {
        CHECKIN, WAIT, CHECKOUT, OPENPROBLEM, COMISSIONING, JOINSESSION, SOLVEPROBLEM, CLOSEPROBLEM, EXIT
    }
    
    Status mystatus;
    String destroyer;                   // Se guardara el nombre del agente Destroyer
    String pos;                         // Auxiliar para sentecias de posicionamiento del agente
    
    String[] mundos = {"Ando", "Bogano", "Coruscant", "D'Qar", "Er'kit", "Fondor"}; //Array con el nombre de los distintos mundos de la P3
    
    String  service = "PManager",       // Servicio a utilizar   
            problem = mundos[0],        // Se guardará el nombre del mundo (problema) a solucionar
            problemManager = "",        // Se guardará (más adelante) el nombre del problem manager de la sesion
            content,                    // Auxiliar para guardar contenido recibido
            sessionKey,                 // LLave de la sesión
            sessionManager,             // Se guardará el nombre del manager de la sesión
            storeManager,               // Se guardará el nombre del agente que controla los sensores
            sensorKeys;                 // Guadará las calves de los sensores
    
    int width, maxFlight, x, y;
    double posxAct, posyAct, poszAct;   // Se guardará la posicion actual del agente
    int iterador = 0;
    double gps[];
    double[] objetivo_punto = new double[3];
    double angular, compass, height;
    
    double[] jedis = new double[50];        // Se alamacenará la posición de los jedis
    int tamJedis = 0;                       // Tamaño del array de jedis   
    
    /**
     * Almacenamiento de memoria del agente
     */
    double[] casillas_x = new double[50];
    double[] casillas_y = new double[50];
    boolean casilla_repe = false;
    double siguiente_x = 0;
    double siguiente_y = 0;
    int it = 0;
    int visual[][] ;
    int thermal[][];
    boolean choca = false;
    boolean calcular_giro = false;
    String giro = "LEFT";
    String password = "GASHAPON";
    String DestroyerPassword = "LARVADESTROYERS";

    
    ACLMessage open, session, corellian2;
    String[] contentTokens, coords, 
    mySensors = new String[] { //Sensores que utilizará el Corellian
        "ONTARGET",            //Muestra si el agente esta o no en la posición del objetivo
        "GPS",                 //Posición del agente en eje de coordenadas
        "COMPASS",             //Da el valor de orientación del agente
        "ANGULAR",             //Da el angulo en el que se encuentra el objetivo
        "ENERGY",              //Muestra la energia de la que dsispone el agente
        
    };
    boolean step = false;
    
   /**
    * Esta función controlará el ciclo de vida de ejecucón del agente
    */
    @Override
    public void setup() {
        super.setup();
        //logger.offEcho();
        exit = false;
        logger.onOverwrite();
        logger.setLoggerFileName("corellian.json");
        //this.enableDeepLARVAMonitoring();
        Info("Setup and configure agent");
        mystatus = Status.CHECKIN;
        exit = false;
        this.myDashboard = new LARVADash(this);
        //this.doActivateLARVADash();
        
        
        
        this.objetivo_punto[0] = -1;
        this.objetivo_punto[1] = -1;
        this.objetivo_punto[2] = -1;
    }

   /**
    * Esta función controlará el ciclo de vida de ejecucón del agente
    */
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
            case WAIT:
                mystatus = MyWait();
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
            case CHECKOUT:
                mystatus = MyCheckout();
                break;
            case EXIT:
            default:
                exit = true;
                break;
        }
    }

    /**
     * Apagar y borrar el agente.
     */
    @Override
    public void takeDown() {
        if (this.AMSIsConnected(this.sessionManager) && this.isCheckedin() ) {
            this.MyCheckout();
        }
        super.takeDown();

    }

    /**
     * Registrará el Corellian en LARVA y lo asociará a nosotros con el passport
     */
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
        DFSetMyServices(new String[]{"CORELLIAN " + password});
        return Status.WAIT;
        
    }

    /**
     * Se pide al problema manager que nos asigne un sessionManger 
     * para abrir una instancia del problema
     */
     public Status MyOpenProblem() {
        if (this.DFGetAllProvidersOf(service).isEmpty()) {
            Error("Service PMANAGER is down");
            return Status.CHECKOUT;
        }

        problemManager = this.DFGetAllProvidersOf(service).get(0);
        Info("Found problem manager " + problemManager);
        this.outbox = new ACLMessage();
        outbox.setSender(getAID());
        outbox.addReceiver(new AID(problemManager, AID.ISLOCALNAME));
        outbox.setPerformative(ACLMessage.REQUEST);
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

    /**
     * Función para salir de LARVA y terminar la ejecución del agente
     */
    public Status MyCheckout() {
        this.doLARVACheckout();
        return Status.EXIT;
    }
    
    /**
     *Función con la cual el Corellian se quedará en espera del Join Session y reclutamiento del destroyer
     */
    public Status MyWait(){
        this.corellian2 = this.LARVAblockingReceive();
        sessionKey = corellian2.getConversationId();
        
        if(corellian2.getPerformative() == ACLMessage.CFP){
            corellian2 = corellian2.createReply();
            corellian2.setPerformative(ACLMessage.AGREE);
            corellian2.setOntology("COMMITMENT");
            corellian2.setConversationId(sessionKey);
            corellian2.setInReplyTo("RECRUITMENT");
            corellian2.setContent("");
            this.LARVAsend(corellian2);
        }
        
        corellian2 = this.LARVAblockingReceive();
        if(corellian2.getPerformative() == ACLMessage.ACCEPT_PROPOSAL){
            corellian2.setInReplyTo("TAKEOFF");
            coords = corellian2.getContent().split(" ");
            x = Integer.parseInt(coords[0]);
            y = Integer.parseInt(coords[1]);
            return Status.COMISSIONING;            
        }else if(corellian2.getPerformative() == ACLMessage.REJECT_PROPOSAL){
            return Status.CHECKOUT;
        }
        
        return Status.CHECKOUT;
    }
    
    /**
     * Función en la que se pedirán los sensores y guardar los sensorKeys de los mismos
     */
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
            outbox.setPerformative(ACLMessage.REQUEST);
            outbox.setContent("Request product "+s+" session "+sessionKey);
            this.LARVAsend(outbox);
            inbox = this.LARVAblockingReceive();
            if(inbox.getContent().startsWith("Confirm")){
                Info("Bought sensor "+s);
                sensorKeys += inbox.getContent().split(" ")[2]+" ";
            } else {
                this.Alert("Sensor "+s+" could not be obtained");
                return Status.CHECKOUT;
            }
        }
        Info("Bought all sensor keys "+sensorKeys);
        return Status.JOINSESSION;
    }

    /**
     * Función para entrar en la sesión del problema, tambíen se indicará la posición inicial del Corellian
     */
    public Status MyJoinSession() {
        String localService ="SESSION MANAGER "+sessionKey;
        if(this.DFGetAllProvidersOf(localService).isEmpty()) {
            Error("Service SESSION MANAGER is down");
            return Status.CHECKOUT;
        }
        sessionManager = this.DFGetAllProvidersOf(localService).get(0);
        Info("Found session manager "+ sessionManager);
        
        outbox = new ACLMessage();
        outbox.setSender(this.getAID());
        outbox.addReceiver(new AID(sessionManager, AID.ISLOCALNAME));
        outbox.setPerformative(ACLMessage.REQUEST);
//        outbox.setContent("Request join session "+sessionKey+" as CORELLIAN at "+x+" "+y+" attach sessionKeyensors "+sensorKeys);
//      "Request join session "+sessionKey+" as FIGHTER at "+x+" "+y+" attach sensors "+sensorKeys
        outbox.setContent("Request join session "+sessionKey+" as CORELLIAN at "+x+" "+y+" attach sensors "+sensorKeys);
        outbox.setConversationId(sessionKey);
        this.LARVAsend(outbox);
        
        
        outbox = this.LARVAblockingReceive();
        String parse[] = outbox.getContent().split(" ");
        Info("ZUMITO ---> " + outbox.getContent());
        destroyer = this.DFGetAllProvidersOf("DESTROYER " + DestroyerPassword).get(0);
        
        if(outbox.getPerformative() == ACLMessage.CONFIRM){
            session = new ACLMessage();
            session.setSender(this.getAID());
            session.addReceiver(new AID(destroyer,AID.ISLOCALNAME));
            session.setPerformative(ACLMessage.INFORM);
            session.setConversationId(sessionKey);
            session.setOntology("COMMITMENT");
            session.setInReplyTo("TAKEOFF");
            session.setContent(x + " " + y);
            this.LARVAsend(session);
            upTo();
            return Status.SOLVEPROBLEM;
        }
        else{
            Alert("Error joining session: "+outbox.getContent());
            return Status.CHECKOUT;
        }
        
    }

    /**
     * Con esta función se informará al destroyer de la posición actual del agente
     * @param x
     * @param y
     * @param z 
     */
    public void informarPos(double x, double y){
        corellian2 = new ACLMessage();
        corellian2.setSender(getAID());
        corellian2.addReceiver(new AID(destroyer,AID.ISLOCALNAME));
        corellian2.setPerformative(ACLMessage.INFORM);
        corellian2.setContent("CAPTURE "+x+" "+y);
        corellian2.setInReplyTo("CAPTURE "+x+" "+y);
        this.LARVAsend(corellian2);
    }
    
    /**
     * Función para recibir coordenadas del destroyer a las que tendra que moverse el agente
     */
    public void recibirMov(){
        open = this.LARVAblockingReceive();
        
        if(open.getPerformative() == ACLMessage.REQUEST){
            String parse[] = open.getContent().split(" ");
            double x =  Double.parseDouble(parse[2]);
            double y =  Double.parseDouble(parse[3]);
            //double z =  Double.parseDouble(parse[3]);
           
            
            corellian2 = new ACLMessage();
            //destroyer2 = session.createReply();
            corellian2.setSender(getAID());
            corellian2.addReceiver(new AID(destroyer,AID.ISLOCALNAME));
            corellian2.setContent("");
            corellian2.setPerformative(ACLMessage.AGREE);
            corellian2.setInReplyTo("CAPTURE "+x+" "+y);
            this.pos = "CAPTURE "+x+" "+y;
            this.LARVAsend(corellian2);
            moveTo(x,y);
        }
    }
    
    /**
     * Función para mover el agente a unas coordenadas pasadas como parametro
     * @param x
     * @param y
     * @param z 
     */
    public void moveTo(double x, double y){
        this.Sensors();
        posxAct = myDashboard.getGPS()[0];
        posyAct = myDashboard.getGPS()[1];
        Info("posx act -->" +posxAct);
        Info("posy act -->" +posyAct);
        

        Point punto = new Point(x,y);
        this.angular = myDashboard.getAngular(punto);
        Info("VOY A IR A LA POS X :"+x);
        Info("VOY A IR A LA POS Y :"+y);
        do{
            this.Sensors();
            posxAct = myDashboard.getGPS()[0];
            posyAct = myDashboard.getGPS()[1];
            
            if( myDashboard.getEnergy() < 750){
                outbox = new ACLMessage();
                outbox.addReceiver(new AID(destroyer,AID.ISLOCALNAME));
                outbox.setSender(getAID());
                outbox.setContent("RECHARGE");
                outbox.setPerformative(ACLMessage.QUERY_IF);
                outbox.setInReplyTo("MOVE "+x+" "+y);
                this.LARVAsend(outbox);
                
                inbox = this.LARVAblockingReceive();
                if(inbox.getPerformative() == ACLMessage.CONFIRM){
                    // Bajamos y recargamos 
                    double alturaActual = myDashboard.getGPS()[2];
                    while (alturaActual > 0){
                        doAction("DOWN");
                        alturaActual -= 5;  
                    }
                    doAction("RECHARGE");
                    upTo();
                }else{
                    this.takeDown();
                }
            }
            
            
            
            
            this.angular = myDashboard.getAngular(punto);
            // Esto no funciona tampoco por algún motivo que desconozco
            if( this.angular != this.compass && abs(this.angular - this.compass) >= 45  && abs(this.angular - this.compass) < 315  ){
                    this.turnTF();
                    if( session.getContent().startsWith("Refuse") || session.getContent().startsWith("Failure")){
                        Alert("Reading of action failed due to "+session.getContent());
                    }
            }else{
                    Info("Valor de mi altura"+ myDashboard.getGPS()[2]);
                    this.doAction("MOVE");
                    //this.Sensors();
            }      
        }while(x!=posxAct || y!=posyAct);
        
        
        Info("------------------------------------------");
        Info("------------------------------------------");
        Info("SALIMOS DEL DO WHILE de MOVERSE A UN PUNTO, ANTES DEL INFORM");
        
        // Ya que estamos en el punto, capturamos al jedi
        this.Sensors();
        //if(myDashboard.getOnTarget()) {
            double alturaActual = myDashboard.getGPS()[2];;
            while (alturaActual > 0){
                doAction("DOWN");
                alturaActual -= 5;  
            }
            doAction("CAPTURE");
            //if(myDashboard.getEnergy() <= 750 ){
                doAction("RECHARGE");
            //}
            
            Info("CAPTURAMOS A UN JEDI"); 
        //}
        
        upTo();
       

        
//        if( this.myDashboard.getEnergy() <= 1500 ){
//            doAction("RECHARGE");
//        }

        informarPos(x,y);     
        
    }
    
    /**
     * Función para subir a una altura determinada por parámetro
     * @param z 
     */
    public void upTo(){
        this.Sensors();
        double alturaActual = myDashboard.getGPS()[2];

        Info("posz act -->" +alturaActual);
        

            while (alturaActual < 220){
                doAction("UP");
                alturaActual += 5;  
            }
          
        
        poszAct = alturaActual;
        Info("posz act fin bucle -->" +alturaActual);
    }
    
    /**
     * Función que definirá el curso que tendrá qeu seguir el agente para contribuir a la solución del problema
     */
    public Status MySolveProblem() {
        recibirMov();
        Info("ACABAMOS 1 ITERACION DEL SOLVEPROBLEM");
        
        
        return Status.SOLVEPROBLEM;
         
    }
    
    /**
     * Función para conseguir el estado de los sensores utilizados
     */
    public void Sensors(){
        ACLMessage session = new ACLMessage();
        session.addReceiver(new AID(sessionManager,AID.ISLOCALNAME));
        session.setPerformative(ACLMessage.QUERY_REF);
        session.setContent("Query sensors session "+sessionKey);
        this.LARVAsend(session);
        
        MessageTemplate t = MessageTemplate.MatchSender(new AID(sessionManager,AID.ISLOCALNAME));
        session = this.LARVAblockingReceive(t);
        if( session.getContent().startsWith("Refuse") || session.getContent().startsWith("Failure")){
            Alert("Reading of sensors failed due to "+session.getContent());
            //return Status.SOLVEPROBLEM;
        }
        this.gps = myDashboard.getGPS();
        this.angular = myDashboard.getAngular();
        this.compass = myDashboard.getCompass();
        double distance = myDashboard.getDistance();
        this.visual = myDashboard.getVisual();
        this.thermal = myDashboard.getThermal();
        
        Info("Reading of GPS\nX="+this.gps[0]+" Y="+this.gps[1]+" Z="+this.gps[2]);
        Info("Reading of compass="+this.compass+"º");
        Info("Reading of angular= "+this.angular+"º");
        Info("Reading of altura="+myDashboard.getGPS()[2]+" de distancia");
        Info("Reading of distance= "+distance+"m");
        String message="Reading of sensor THERMAL;\n"; 
//        for(int y=0; y<this.thermal.length; y++){
//            for(int x=0; x<this.thermal[0].length; x++){
//                message += String.format("%03d ", this.thermal[y][x]);
//                
//                if(this.thermal[y][x] == 0.0){
//                    double new_x = this.gps[0]+(x-10);
//                    double new_y = this.gps[1]+(y-10);
//                    
//                    if(!jediEncontrado(new_x,new_y)){
//                        Info("HEMOS ENCONTRADO A UN JEDI, ESTA EN LA POSICION X=" + new_x + ", Y=" + new_y);
//                        ACLMessage outbox = new ACLMessage();
//                        outbox.addReceiver(new AID(destroyer, AID.ISLOCALNAME));
//                        outbox.setPerformative(ACLMessage.INFORM_REF);
//                        outbox.setContent("FOUND "+new_x+" "+new_y);
//                        outbox.setInReplyTo(this.pos);
//                        this.LARVAsend(outbox);
//                        
//                        this.jedis[this.tamJedis] = new_x; tamJedis++;
//                        this.jedis[this.tamJedis] = new_y; tamJedis++;
//                    }
//                }
//            }
//            message += "\n";
//        }
        Info(message);
         
        //return Status.
    }
    
    /**
     * Función que indicará si el agente ha encontrado un Jedi en unas coords dadas
     * @param pos_x
     * @param pos_y
     * @return Boolean verdadero si ha encontrado un jedi
     */
    public boolean jediEncontrado(double pos_x, double pos_y){
        boolean find = false;
        
        for(int i=0; i<this.jedis.length && !find; i+=2){
            if(pos_x == this.jedis[i] && pos_y == this.jedis[i+1])
                find = true;
        }
        
        return find;
    }

     /**
     * Función para que el agente realice una acción dada
     */
    public void doAction(String action) {
        ACLMessage session = new ACLMessage();
        session.addReceiver(new AID(sessionManager,AID.ISLOCALNAME));
        session.setPerformative(ACLMessage.REQUEST);
        session.setContent("Request execute " + action + " session "+sessionKey);
        this.LARVAsend(session);
        
        MessageTemplate t = MessageTemplate.MatchSender(new AID(sessionManager,AID.ISLOCALNAME));
        session = this.LARVAblockingReceive(t);
        if(session.getContent().startsWith("Failure")){
            this.takeDown();
        }
    }
    
    /**
     * Función para girar el Corellian en una dirección
     */
    public void turnTF() {
        if( this.compass < this.angular ){
            if( (this.angular-180) > this.compass ){
                    this.doAction("RIGHT");
                    //this.Sensors(); 
            }else{
                    this.doAction("LEFT");
                    //this.Sensors(); 
            }

        }else if( this.compass > this.angular ){
            if( (this.compass - 180) > this.angular ){
                    this.doAction("LEFT");
                    //this.Sensors(); 
            }else {
                    this.doAction("RIGHT");
                    //this.Sensors(); 
            }
        }
    }
    
    /**
     * Función para calcular la altura de la siguiente casilla
     * @return Double con la siguiente altura
     */
    public double calculateNextHeight() {
        double res = 0;
        this.Sensors();
        
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
        
        for(int i=0; i < 50; i++){
            if( this.casillas_x[i] == this.siguiente_x && this.casillas_y[i] == this.siguiente_y){
                this.casilla_repe = true;
            }
        }
        
        return res;
    }
    
    /**
     * Función de recarga
     */
    public void rechargeTF() {
        /*if( myDashboard.getEnergy() < 1000 ){
            while( myDashboard.getGPS()[2] < maxFlight){
                this.doAction("DOWN");
                this.Sensors();
            }

            this.doAction("RECHARGE");
        }*/

        //Empieza aqui
        /*
        ACLMessage confirm;
        if( myDashboard.getEnergy() < 100 ){
            
            ACLMessage outbox = new ACLMessage();
            outbox.addReceiver(new AID(destroyer, AID.ISLOCALNAME));
            outbox.setPerformative(ACLMessage.QUERY_IF);
            outbox.setContent("RECHARGE");
            outbox.setConversationId(sessionKey);
            this.LARVAsend(outbox);
            
            
            confirm = this.LARVAblockingReceive();
            if(confirm.getPerformative() == ACLMessage.CONFIRM){
                
                while( myDashboard.getGPS()[2] < maxFlight){
                   this.doAction("DOWN");
                   this.Sensors();
                }
                this.doAction("RECHARGE");
                
            }else if(confirm.getPerformative() == ACLMessage.DISCONFIRM){
                this.takeDown();
            }
        }*/
        
    }
    
    /**
     * Función para cambiar el giro
     */
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
