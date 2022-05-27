import java.rmi.*;
import java.rmi.server.UnicastRemoteObject;
//import java.net.MalformedURLException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.util.ArrayList;


public class Servidor implements I_Donaciones{
    // Arraylist con los usuarios del sistema
    private ArrayList<String> usuarios;
    // Total local de las donaciones
    private double totalLocal;
    // Referencia a la replica seleccionada 
    private I_Donaciones replicaSelec;
    // Arraylist con todas las replicas 
    private ArrayList<I_Donaciones>  replicas;
    // Arraylist que guarda un registro de las donaciones 
    private ArrayList<Donaciones> Registro;

    // Constructor sin parámetros
    public Servidor(){
        super();
        totalLocal = 0;
        usuarios = new ArrayList<String>();
        Registro = new ArrayList<Donaciones>();
        replicas = new ArrayList<I_Donaciones>();

    }

    /***************************************************************/
    /*       Métodos clave de la funcionalidad del servidor        */
    /***************************************************************/
    @Override
    public void registrar(String usuario) throws RemoteException{
        obtenerReplica(0,usuario);
        if(this.replicaSelec != null){
            this.replicaSelec.addUsuario(usuario);
            System.out.println("El usuario "+ usuario + " ha sido registrado con éxito");
        }
    }

    @Override
    public void donar(String usuario,double cantidad) throws RemoteException{
        
        if(cantidad > 0){
            obtenerReplica(1,usuario);
            if(this.replicaSelec != null)
            {
                this.replicaSelec.incrementarTotal(cantidad);
                Donaciones aport = new Donaciones(usuario, cantidad);
                this.replicaSelec.addDonacion(aport);
                System.out.println("El usuario " + usuario + " ha donado " + cantidad + " euros");
            }
        }else
        {
            System.out.println("Se ha intentado donar una cantidad no válida");
        }
    }

    @Override
    public double getTotal(String usuario) throws RemoteException{
        obtenerReplica(2,usuario);
        if(this.replicaSelec != null)
        {
            double total = this.replicaSelec.getTotalLocal();            
            return total;
        }
        else{
            System.out.println("Es necesario realizar una donación para poder consultar el total local aportado");
            return 0.0;
        }
    }

    public double getTotalLocal() throws RemoteException{
        return this.totalLocal;
    }
    
    public double getTotalGlobal(String usuario) throws RemoteException{
        double totalGlobal = 0.0;
        obtenerReplica(2,usuario);
        if(this.replicaSelec != null){
            for(int i = 0; i < this.replicas.size(); i++){
                totalGlobal += this.replicas.get(i).getTotalLocal();
            }
            return totalGlobal;
        }
        else{
            System.out.println("Es necesario realizar una donación para poder consultar el total global aportado");
            return 0.0;
        }
    }
          
    
    /***************************************************************/
    /*      Métodos auxiliares para el registro de donaciones      */
    /***************************************************************/
    public void addDonacion(Donaciones donacion) throws RemoteException{
        this.Registro.add(donacion);
    }

    public ArrayList<Donaciones> getRegistro() throws RemoteException{
        return this.Registro;
    }


    /**********************************************************************/
    /* Métodos auxiliares para la consulta y modificación de los usuarios */
    /**********************************************************************/
    public void addUsuario(String usuario) throws RemoteException{
        this.usuarios.add(usuario);
    }

    public ArrayList<String> getUsuarios() throws RemoteException{
        return this.usuarios;
    }

    public ArrayList<String> getUsuarioLocales() throws RemoteException{
        ArrayList<String> usuariosLocales = new ArrayList<String>();
        for(int i = 0; i < this.usuarios.size(); i++){
            usuariosLocales.add(this.usuarios.get(i));
        }
        return usuariosLocales;
    }

    public ArrayList<String> getUsuarioGlobales() throws RemoteException{
        ArrayList<String> usuariosGlobales= new ArrayList<String>();
        for(int i = 0; i < this.replicas.size(); i++){
            for(int j = 0; j < this.replicas.get(i).getUsuarios().size(); j++){
                usuariosGlobales.add(this.replicas.get(i).getUsuarios().get(j));
            }
        }
        return usuariosGlobales;
    }
    
    
    /***************************************************************/
    /*                Métodos auxiliares extra                     */
    /***************************************************************/
    
    public void incrementarTotal(double cantidad) throws RemoteException{
        this.totalLocal += cantidad;
    }

    public void enlazarServidores(String ubi, String nombre, int nReplicas){
        try {
            if(nReplicas == 2){
                Registry registry = LocateRegistry.getRegistry(ubi);
                //En el registro localhost miro el nombre 
                I_Donaciones aux = (I_Donaciones) registry.lookup(nombre);
                
                // Añado referencias a la lista de replicas
                this.replicas.add(aux);
                this.replicas.add(this);

                // Añado las referencias al servidor original
                aux.asignarReferencia(this);
                aux.asignarReferencia(aux);

                System.out.println("2 Servidores enlazados correctamente");
            }
            if(nReplicas == 3){
                Registry registry = LocateRegistry.getRegistry(ubi);
                I_Donaciones aux = (I_Donaciones) registry.lookup("Original");
                I_Donaciones aux3 = (I_Donaciones) registry.lookup("Replica2");
                
                aux.asignarReferencia(aux3);
                aux.asignarReferencia(aux);

                aux3.asignarReferencia(aux3);
                aux3.asignarReferencia(aux);
                
                System.out.println("3 Servidores enlazados correctamente");
            }
        } catch (Exception e){
            System.err.println("Error al enlazar los servidores");
            e.printStackTrace();
        }
    }
    
    public ArrayList<I_Donaciones> obtenerReplicas()throws RemoteException{
        return this.replicas;
    }
    
    public void asignarReferencia(I_Donaciones ref) throws RemoteException{
        this.replicas.add(ref);
    }
    
    private void obtenerReplica(int opcion, String usuario )throws RemoteException{
        Boolean encontrado = false;
            switch(opcion){
                //Registrar
                case 0:
                    this.replicaSelec = null;
                    for(int i = 0; i < this.replicas.size() && !encontrado; i++){
                        if(this.replicas.get(i).getUsuarios().contains(usuario)){
                            this.replicaSelec = this.replicas.get(i);
                            encontrado = true;
                        }
                    }
                        
                    if(encontrado){
                        System.err.println("Error usuario que quiere registrar ya se encuentra en alguna réplica");
                        this.replicaSelec = null;
                    }
                    else{
                        this.replicaSelec = this;
                        for(int i = 0; i < this.replicas.size(); i++){
                            if(this.replicaSelec.getUsuarios().size() >= this.replicas.get(i).getUsuarios().size() ){
                                this.replicaSelec = this.replicas.get(i);
                            }
                                
                        }
                    }
                break;
                
                //Donar
                case 1:
                    encontrado = this.usuarios.contains(usuario);
                    for(int i = 0; i < this.replicas.size() && !encontrado; i++  ){
                        if(this.replicas.get(i).getUsuarios().contains(usuario)){
                            this.replicaSelec = this.replicas.get(i);
                            encontrado = true;
                        }
                    }
                    if(!encontrado){
                        System.err.println("Error el usuario no está registrado");
                        this.replicaSelec = null;
                    }
                break;
                
                //Consultar
                case 2:
                    boolean valido = false;
                    for(int j = 0; j < this.getRegistro().size() && !valido; j++){
                        if( this.getRegistro().get(j).getUser().equals(usuario)){
                            valido = true;
                            this.replicaSelec = this;
                        }   
                    }
                        
                    for(int i = 0; i < this.replicas.size() && !valido; i++){
                        for(int j = 0; j < this.replicas.get(i).getRegistro().size() && !valido; j++){
                            if( this.replicas.get(i).getRegistro().get(j).getUser().equals(usuario)){
                                valido = true;
                                this.replicaSelec = this.replicas.get(i);
                            }   
                                
                        }
                    }
                        if(!valido)
                        this.replicaSelec = null;
                        
                break;
                        
            }
    }
    
    public static void main(String[] args) {
        if(args.length < 2){
            System.out.println("Error: uso correcto -> java Servidor <IP> <0> (primer servidor) | <1|2|..> si ya existe el primer servidor>");
            System.exit(0);
        }
                
        if (System.getSecurityManager() == null) {
            System.setSecurityManager(new SecurityManager());
        }
                
        try {
            String nombre_objeto_remoto = "";
            switch(args[1]){
                case "0":
                    nombre_objeto_remoto = "Original";
                break;

                case "1":
                    nombre_objeto_remoto = "Replica";
                break;

                case "2":
                    nombre_objeto_remoto = "Replica2";
                break;
            }
                    
            I_Donaciones servidor= new Servidor();
            I_Donaciones  stub = (I_Donaciones ) UnicastRemoteObject.exportObject(servidor, 0);
            Registry registry = LocateRegistry.getRegistry();
            registry.rebind(nombre_objeto_remoto, stub);
                    
            if(Integer.parseInt(args[1]) == 1){
                ((Servidor) servidor).enlazarServidores(args[0],"Original",2);
            }
                    
            if(Integer.parseInt(args[1]) == 2){
                ((Servidor) servidor).enlazarServidores(args[0],"Replica2",3);
            }
                    
            System.out.println("Servidor iniciado");
        } catch (Exception e) {
            System.err.println("exception");
            e.printStackTrace();
        }          
    }
}