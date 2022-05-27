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
// @author código: Todos hemos participado en la creación de los distintos métodos ya que fue la primera
// nave que implementamos, lo único que podemos destacar de manera más aislada es la realización de la 
// función "moverFightersCorellian" por parte de los compañeros Rubén y Agustin.
//------------------------------------------------------------------------------------------------------------


import agents.LARVAFirstAgent;
import jade.core.AID;
import jade.lang.acl.ACLMessage;
import jade.lang.acl.MessageTemplate;
import static java.lang.Math.abs;
import java.util.*;
import swing.LARVADash;
import java.util.Random;


// CODIGO DEL DESTROYER
public class Destroyer extends LARVAFirstAgent{
     // Posibles estados del Destroyer para definir su ejecución
     enum Status {
        CHECKIN, CHECKOUT, OPENPROBLEM, COMISSIONING, JOINSESSION, SOLVEPROBLEM, CLOSEPROBLEM, EXIT
    }
    Status mystatus;
    String nombre_fighter;                                                          // Nombre para conseguir instanciar al fighter
    String[] mundos = {"Ando", "Bogano", "Coruscant", "DQar", "Erkit", "Fondor"};   // Array con el nombre de los distintos mundos de la P3
    
    String  service = "PManager",   // Servicio a utilizar                                                       
            problem = mundos[5],    // Se guardará el nombre del mundo (problema) a solucionar
            problemManager = "",    // Se guardará (más adelante) el nombre del problem manager de la sesion
            mymap,                  // Se almacenará el mapa completo tras subir a máxima al altura para compartirlo con los demás
            content,                // Auxiliar para guardar contenido recibido
            sessionKey,             // LLave de la sesión
            sessionManager,         // Se guardará el nombre del manager de la sesión
            storeManager,           // Se guardará el nombre del agente que controla los sensores
            sensorKeys;             // Guadará las calves de los sensores
    
    int     height,                 // Altura del mapa
            width,                  // Anchura del mapa
            maxFlight,              // Altura máxima de vuelo permitida en el mundo
            contTF = 0;             // Contador de TieFighters reclutados
    
    double maxHeight;               // Altura máxima en el mapa
    int posxTF1, posyTF1,           // Posiciones x e y de TieFighter1
        posxTF2, posyTF2,           // Posiciones x e y de TieFighter2
        posxCOR1, posyCOR1,         // Posiciones x e y de Corellian1
        posxCOR2, posyCOR2;         // Posiciones x e y de Corellian2
    
    int availRecharges = 5;         // Recargas restantes a repartir entre los agentes
    
    String password = "LARVADESTROYERS";
    String tfPasswd = "CORBATALUCHADORA";
    String corPasswd = "GASHAPON";
    
    ACLMessage open, session;
    AID TF1, TF2, COR1, COR2;
    String tf1, tf2, cor1, cor2;
    
    String[] contentTokens, 
    mySensors = new String[] {      // Sensores que utilizará el Destroyer
          "GPS",                    // Posición del agente en eje de coordenadas
    };
    boolean step = false;
    
    double x = 1;
    double y = 1;
    double gps[];
    
    /* Puntos a enviar para realizar el barrido */
    double[] puntos_x_TF1 =  { 20.0,20.0, 20.0, 20.0, 20.0,30.0, 30.0, 30.0 , 30.0 , 30.0 , 30.0};
    double[] puntos_y_TF1 =  { 15.0,30.0, 45.0, 60.0, 70.0,60.0, 45.0, 30.0 , 15.0 , 10.0 , 5.0};
    double[] puntos_x_TF2 =  { 70.0,70.0, 70.0, 70.0,70.0,50.0, 50.0, 50.0 , 50.0 , 50.0, 50.0};
    double[] puntos_y_TF2 =  { 15.0,30.0, 45.0, 60.0, 70.0,60.0, 45.0, 30.0 , 15.0 , 10.0 , 5.0};
    
    /* Vector para almacenar los jedis encontrados */
    double[] jedis_x = new double[50];
    double[] jedis_y = new double[50];
    int tamJedis = 0;               // Tamaño de los array de Jedis
    
    
    
   /**
    * Función para inicializar y configurar el agente
    */
    @Override
    public void setup(){
       super.setup();
       //logger.onEcho();
       exit = false;
       logger.onOverwrite();
       logger.setLoggerFileName("practica3.json");
       //this.enableDeepLARVAMonitoring();
       Info("Setup and configure agent");
        mystatus = Status.CHECKIN;
        exit = false;
        this.myDashboard = new LARVADash(this);
        //this.doActivateLARVADash();
    }

    
    /**
     * Cuerpo principal del ciclo de vida
     * Función que ejecuta paso a paso o del tirón, todos los estados que conforman el ciclo de vida del agente
     * Termina cuando la variable exit == true, en caso contrario se repite de nuevo
     */
    @Override
    public void Execute (){
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

    
    /**
     * Función que realiza el cierre y la borrado del agente
     */
    @Override
    public void takeDown() {
        if (this.AMSIsConnected(this.sessionManager)&& this.isCheckedin()) {
            this.MyCloseProblem();
            this.MyCheckout();
        }
        Info("Take Down");
        super.takeDown();
    }

    
    /**
     * Registrará el Destroyer en LARVA y lo asociará a nosotros con el passport
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
        DFSetMyServices(new String[]{"DESTROYER " + password});
        return Status.OPENPROBLEM;
    }

    
    /**
     * Función para salir de LARVA y terminar la ejecución del agente
     */
    public Status MyCheckout() {
        this.doLARVACheckout();
        return Status.EXIT;
    }

    
    /**
     * Función para abrir la instancia de un problema por medio del PManager
     * El PManager nos asignará un SessioneManager durante todo el problema
     * (este método solo lo realizará el destroyer)
     */
    public Status MyOpenProblem() {
        if (this.DFGetAllProvidersOf(service).isEmpty()) {
            Error("Service PMANAGER is down");
            return Status.CHECKOUT;
        }
        
        problemManager = this.DFGetAllProvidersOf(service).get(0);
        Info("Found problem manager " + problemManager);
        
        int nAgents;
        do{
            nAgents = 0;
            nAgents += DFGetAllProvidersOf("FIGHTER " + tfPasswd).size();
        }while(nAgents < 2);
        
        do{
            nAgents = 0;
            nAgents += DFGetAllProvidersOf("CORELLIAN " + corPasswd).size();
        }while(nAgents < 2);
        
        
        
        this.outbox = new ACLMessage();
        outbox.setSender(getAID());
        outbox.addReceiver(new AID(problemManager, AID.ISLOCALNAME));
        outbox.setContent("Request open " + problem +" alias "+password);
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
     * Cerrará la instancia del problema y pedirá Checkout a cada uno de los agentes reclutados
     */
    public Status MyCloseProblem() {
        ACLMessage outbox_crew = new ACLMessage();
        outbox_crew.addReceiver(TF1);
        outbox_crew.addReceiver(TF2);
        outbox_crew.addReceiver(COR1);
        outbox_crew.addReceiver(COR2);
       
        outbox_crew.setOntology("COMMITMENT");
        outbox_crew.setConversationId(sessionKey);
        outbox_crew.setPerformative(ACLMessage.CANCEL);
        outbox_crew.setContent("Cancel crew");
        this.LARVAsend(outbox_crew);
    
        outbox = open.createReply();
        //outbox.addReceiver(new AID(problemManager,AID.ISLOCALNAME));
        outbox.setPerformative(ACLMessage.CANCEL);
        outbox.setConversationId(sessionKey);
        outbox.setOntology("COMMITMENT");
        outbox.setContent("Cancel session " + sessionKey);
        Info("Closing problem Helloworld, session " + sessionKey);
        this.LARVAsend(outbox);
        inbox = LARVAblockingReceive();
        Info(problemManager + " says: " + inbox.getContent());
        return Status.CHECKOUT;
    }

    
    /**
     * Función en la que se pedirán los sensores y guardar los sensorKeys de los mismos
     */
    public Status MyComissioning() {
        // Se establece comunicación con un Store Manager
        String localService ="STORE "+sessionKey;
        if(this.DFGetAllProvidersOf(localService).isEmpty()) {
            Error("Service STORE is down");
            return Status.CLOSEPROBLEM;
        }
        storeManager = this.DFGetAllProvidersOf(localService).get(0);
        Info("Found store manager "+ storeManager);
        
        // Se piden las sensorKeys al StoreManager
        sensorKeys = "";
        for(String s: mySensors){
            outbox = new ACLMessage();
            outbox.setSender(this.getAID());
            outbox.addReceiver(new AID(storeManager, AID.ISLOCALNAME));
            outbox.setConversationId(sessionKey);
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

    
    /**
     * Función para entrar en la sesión del problema, tambíen se indicará la posición inicial del Destroyer
     */
    public Status MyJoinSession() {
        outbox = session.createReply();
        outbox.setPerformative(ACLMessage.REQUEST);
        // Se pide entrar en la sesion en un punto con los distintos sensores.
        outbox.setContent("Request join session "+sessionKey+" as Destroyer at 0 0 attach sensors "+sensorKeys);
        this.LARVAsend(outbox);
               
        session = this.LARVAblockingReceive();
        Info("Contenido del inbox: "+ session.getContent());
        
        String parse[] = session.getContent().split(" ");  
        if(session.getPerformative() == ACLMessage.CONFIRM){
            Info("Se recibe el contenido");
            width = Integer.parseInt(parse[8]);
            height = Integer.parseInt(parse[10]);
            maxFlight = Integer.parseInt(parse[14]);
            return Status.SOLVEPROBLEM;
        }
        else{
            Alert("Error joining session: "+session.getContent());
            return Status.CLOSEPROBLEM;
        }        
    }
    
    
    /**
     * Función utilizada para subir a máxima altura el Destroyer 
     * y así pedir el mapa completo para poder compartirlo con los demás agentes
     */
    public void getMap(){
        this.Sensors();
        // Subir hasta altura máxima
        while(myDashboard.getGPS()[2] < maxFlight){
            doAction("UP");
            this.Sensors();
        }
        
        // Pedir el mapa al Session Manager
        outbox = session.createReply();
        outbox.setPerformative(ACLMessage.QUERY_REF);
        outbox.setContent("Query map session "+sessionKey);
        this.LARVAsend(outbox);
        
        session = this.LARVAblockingReceive();
        if( session.getContent().startsWith("Refuse") || session.getContent().startsWith("Failure")){
            Alert("Reading of map failed due to "+session.getContent());
        }
        
        // Guardamos el mapa
        mymap = session.getContent();
    }
    
    
    /**
     * Función para reclutar a las diferentes naves (Tie Fighters y Corellians)
     */
    public void reclutarTieCor(){
        this.outbox = new ACLMessage(ACLMessage.CFP);
        outbox.setContent(mymap);
        outbox.setOntology("COMMITMENT");
        
        // Se añaden como receptores los distintos TieFighters y Corellian existentes
        for(int i = 0; i < this.DFGetAllProvidersOf("FIGHTER "+ tfPasswd).size(); i++){
            outbox.addReceiver(new AID(this.DFGetAllProvidersOf("FIGHTER "+ tfPasswd).get(i), AID.ISLOCALNAME));
        }
        for(int i = 0; i < this.DFGetAllProvidersOf("CORELLIAN "+ corPasswd).size(); i++){
            outbox.addReceiver(new AID(this.DFGetAllProvidersOf("CORELLIAN "+ corPasswd).get(i), AID.ISLOCALNAME));
        }
        
        // Establecemos los AID (identificadores) de las diversas naves
        TF1 = new AID(this.DFGetAllProvidersOf("FIGHTER "+ tfPasswd).get(0), AID.ISLOCALNAME);
        TF2 = new AID(this.DFGetAllProvidersOf("FIGHTER "+ tfPasswd).get(1), AID.ISLOCALNAME);
        COR1 = new AID(this.DFGetAllProvidersOf("CORELLIAN "+ corPasswd).get(0), AID.ISLOCALNAME);
        COR2 =  new AID(this.DFGetAllProvidersOf("CORELLIAN "+ corPasswd).get(1), AID.ISLOCALNAME);
        
        // Respondemos al mensaje de reclutar
        outbox.setReplyWith("RECRUITMENT");
        outbox.setConversationId(sessionKey); 
        this.LARVAsend(outbox);
        
        MessageTemplate t = MessageTemplate.MatchInReplyTo("RECRUITMENT");
        int numTfCor = this.DFGetAllProvidersOf("FIGHTER " + tfPasswd).size() + this.DFGetAllProvidersOf("CORELLIAN " + corPasswd).size();
        
        for(int i = 0; i < numTfCor; i++){
            open = this.LARVAblockingReceive(t);
            if(open.getPerformative() == ACLMessage.AGREE){
                session = open.createReply();
                session.setPerformative(ACLMessage.ACCEPT_PROPOSAL);
                session.setConversationId(sessionKey);
                session.setOntology("COMMITMENT");
                // Dependiendo de la nave, establecemos su pos incial
                if(open.getSender().equals(TF1) ){
                    posxTF1 = width/4;
                    posyTF1 = height/4;
                    session.setContent(posxTF1 + " " + posyTF1);
                }
                else if(open.getSender().equals(TF2)){
                    posxTF2 = width - width/4;
                    posyTF2 = height - height/4;
                    session.setContent(posxTF2 + " " + posyTF2);
                }
                else if(open.getSender().equals(COR1)){
                    posxCOR1 = width/4;
                    posyCOR1 = height/4 + 5;
                    session.setContent(posxCOR1 + " " + posyCOR1);
                }
                else if(open.getSender().equals(COR2)){
                    posxCOR2 =width - width/4;
                    posyCOR2 = height - height/4 + 5;
                    session.setContent(posxCOR2 + " " + posyCOR2);
                }
            
                session.setReplyWith("TAKEOFF");
                this.LARVAsend(session);
            }
            else{
                session = open.createReply();
                session.setPerformative(ACLMessage.REJECT_PROPOSAL);
                session.setConversationId(sessionKey);
                session.setOntology("COMMITMENT");
                session.setContent("Cancel crew");
                this.LARVAsend(session);
            }
        }
    }

    
    /**
     * Función para conseguir el estado de los sensores utilizados (solo gps en este caso)
     */
    public void Sensors(){
        session = session.createReply();
        session.setPerformative(ACLMessage.QUERY_REF);
        session.setContent("Query sensors session "+sessionKey);
        this.LARVAsend(session);
        
        // Leer sensores
        MessageTemplate t = MessageTemplate.MatchSender(new AID(sessionManager,AID.ISLOCALNAME));
        session = this.LARVAblockingReceive(t);
        if( session.getContent().startsWith("Refuse") || session.getContent().startsWith("Failure")){
            Alert("Reading of sensors failed due to "+session.getContent());
        }
        
        // Escribir por pantalla los datos que ha leido el GPS
        this.gps = myDashboard.getGPS();
        Info("Reading of GPS\nX="+this.gps[0]+" Y="+this.gps[1]+" Z="+this.gps[2]);
    }

   
    /**
     * Función para conseguir la altura máxima del mapa
     */
    public void getMaxHeightMap(){
        maxHeight = 0;
        for(int i = 0; i < width; i++){
            for(int j=0; j < height; j++){
                if(myDashboard.getMapLevel(i, j) > maxHeight && myDashboard.getMapLevel(i, j) < 500){
                    maxHeight = myDashboard.getMapLevel(i, j);
                }
            }
        }
                
        MessageTemplate t2 = MessageTemplate.MatchInReplyTo("TAKEOFF");
        double x,y;
        for(int i = 0; i<this.DFGetAllProvidersOf("FIGHTER "+ tfPasswd).size(); i++){
            open = this.LARVAblockingReceive(t2);
        }
        for(int i = 0; i<this.DFGetAllProvidersOf("CORELLIAN "+ corPasswd).size(); i++){
            open = this.LARVAblockingReceive(t2);
        }
    }
    
    
    /**
     * Función que indicará a los agentes TieFighters y correlian donde tendrán que moverse
     * y almacenar/enviar/capturar las diferentes posiciones de los jedis
     */
    public void moverFightersCorellian(){
        int iterador = 0;
        double x = 0, y = 0;
        
        do{
            // ENVIAMOS LOS PUNTOS A DONDE SE VAN A MOVER CADA FIGHTER
            for(int i = 0; i<this.DFGetAllProvidersOf("FIGHTER "+ tfPasswd).size(); i++){
                ACLMessage outbox = new ACLMessage();
                if(open.getPerformative() == ACLMessage.INFORM && i==0){
                    x = this.puntos_x_TF1[iterador];
                    y = this.puntos_y_TF1[iterador];
                    outbox.addReceiver(TF1);
                }else{
                    x = this.puntos_x_TF2[iterador];
                    y = this.puntos_y_TF2[iterador];
                    outbox.addReceiver(TF2);
                }
                
                outbox.setContent("MOVE "+x+" "+y+" "+(maxHeight+5));
                outbox.setPerformative(ACLMessage.REQUEST);
                outbox.setReplyWith("MOVE "+x+" "+y+" "+(maxHeight+5));
                this.LARVAsend(outbox);
                
                // DEBEMOS DE ESPERAR AL AGREE DE CADA UNO DE ELLOS 
                MessageTemplate t = MessageTemplate.MatchInReplyTo("MOVE "+x+" "+y+" "+(maxHeight+5));
                Info("---------------------------------------");
                Info("Primer blocking receive (AGREE) :"+i);
                ACLMessage prueba = new ACLMessage();
                prueba = this.LARVAblockingReceive(t);
                
                Info("---------------------------------------");
                Info("Segundo blocking receive (INFORM) o (INFORM-REF) :"+i);
                
                
                // ESPERAMOS AL INFORM DE QUE HAYAN LLEGADO A SUS RESPECTIVOS DESTINOS Y VUELVE A COMENZAR EL CICLO
                // MIENTRAS SE ESPERA AL INFORM DEBERIAMOS RECIBIR LAS POSICIONES DE LOS JEDIS
                do{
                    ACLMessage open = new ACLMessage();
                    open = this.LARVAblockingReceive(t);
                    if(open.getPerformative() == ACLMessage.INFORM_REF){
                        // Codigo donde Almacenar pos x y de Jedi o enviar directamente a Correllian
                        String[] parse = open.getContent().split(" ");       
                        double jedi_x = Double.parseDouble(parse[1]);
                        double jedi_y = Double.parseDouble(parse[2]);
                        //if(!jediEncontrado(jedi_x,jedi_y)){
                            
                            ACLMessage capture = new ACLMessage();  
                            if( open.getSender().equals(TF1)){
                                capture.addReceiver(COR1);  
                            }else if(open.getSender().equals(TF2)){
                                capture.addReceiver(COR2);
                            }
                            
                            this.jedis_x[this.tamJedis] = jedi_x;
                            this.jedis_y[this.tamJedis] = jedi_y;
                            Info(open.getContent());
                            Info("Nos ha llegado las posiciones x:"+this.jedis_x[this.tamJedis]+" y:"+this.jedis_y[this.tamJedis]);
                            this.tamJedis++;
                            
                            capture.setContent("REQUEST CAPTURE "+jedi_x+" "+jedi_y);
                            capture.setPerformative(ACLMessage.REQUEST);
                            capture.setReplyWith("CAPTURE "+jedi_x+" "+jedi_y);
                            this.LARVAsend(capture);
                            
                            MessageTemplate cap = MessageTemplate.MatchInReplyTo("CAPTURE "+jedi_x+" "+jedi_y);
                            Info("---------------------------------------");
                            Info("Primer blocking receive (AGREE) :");
                            ACLMessage inbox_cap = new ACLMessage();
                            inbox_cap = this.LARVAblockingReceive(cap);
                            Info("---------------------------------------");
                            Info("Segundo blocking receive (INFORM) :");
                            // ESPERAMOS AL INFORM DE QUE HAYAN LLEGADO A SUS RESPECTIVOS DESTINOS Y CAPTURADO Y VUELVE A COMENZAR EL CICLO
                            // MIENTRAS SE ESPERA AL INFORM PODRIAMOS RECIBIR QUERY_IF DE RECHARGE POR PARTE DE LOS CORELLIANS
                            do{
                                inbox_cap = this.LARVAblockingReceive();
                                if(inbox_cap.getPerformative() == ACLMessage.QUERY_IF){
                                    ACLMessage recharge = new ACLMessage();
                                    recharge = inbox_cap.createReply();
                                    if( this.availRecharges > 0){
                                    recharge.setPerformative(ACLMessage.CONFIRM);
                                    this.availRecharges--;
                                }else{
                                    recharge.setPerformative(ACLMessage.DISCONFIRM);
                                }
                                    this.LARVAsend(recharge);
                                }
                            }while(inbox_cap.getPerformative() != ACLMessage.INFORM);

                            
                           
                        //}
                    }else if( open.getPerformative() == ACLMessage.QUERY_IF  ){
                        ACLMessage recharge = new ACLMessage();
                        recharge = open.createReply();
                        if( this.availRecharges > 0){
                            recharge.setPerformative(ACLMessage.CONFIRM);
                            this.availRecharges--;
                        }else{
                            recharge.setPerformative(ACLMessage.DISCONFIRM);
                        }
                        this.LARVAsend(recharge);
                        
                    }
                }while(open.getPerformative() != ACLMessage.INFORM);
                
            }
           
            iterador++;
            Info("ENVIAMOS LOS SIGUIENTES PUNTOS");
        }while(iterador < this.puntos_x_TF1.length);
       
       
            
            
    }
    
    
    /**
     * Función que indicará si el agente ha encontrado un Jedi en unas coords dadas
     * @param pos_x
     * @param pos_y
     * @return Boolean verdadero si ha encontrado un jedi
     */
    public boolean jediEncontrado(double pos_x, double pos_y){
        boolean find = false;
        
        for(int i=0; i<this.tamJedis && !find; i++){
            if(pos_x == this.jedis_x[i] && pos_y == this.jedis_y[i])
                find = true;
        }
        
        return find;
    }
    
    
    /**
     * Función que muestra por pantalla todos los puntos de los Jedis
     */
    public void recorrerJedis(){
        for(int i=0; i<this.tamJedis ; i++){
            Info("Jedi numero :"+i+" Pos_x :"+this.jedis_x[i]+" Pos_y :"+this.jedis_y[i]);
        }
    }
    
    
    /**
     * Función que describirá el curso que seguirá el Destroyer para conseguir el éxito en la misión
     */
    public Status MySolveProblem() {
        Sensors();
        getMap();
        reclutarTieCor();  
        
        getMaxHeightMap();
        
        moverFightersCorellian();
        
        recorrerJedis();   
        
        return Status.CLOSEPROBLEM; 
    }
    
    
    /**
     * Función para que el agente realice una acción dada
     * @param action
     */
    public void doAction(String action) {
        ACLMessage session = new ACLMessage();
        session.addReceiver(new AID(sessionManager,AID.ISLOCALNAME));
        session.setPerformative(ACLMessage.REQUEST);
        session.setContent("Request execute " + action + " session "+sessionKey);
        this.LARVAsend(session);
        
        MessageTemplate t = MessageTemplate.MatchSender(new AID(sessionManager,AID.ISLOCALNAME));
        session = this.LARVAblockingReceive(t);
    }
}
