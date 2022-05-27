import java.rmi.Remote;
import java.rmi.RemoteException;
import java.util.ArrayList;


public interface I_Donaciones extends Remote
{
    // Métodos clave de la funcionalidad del servidor
    void registrar(String usuario) throws RemoteException;
    void donar(String usuario,double cantidad) throws RemoteException;
    double getTotal(String usuario) throws RemoteException; 
    double getTotalLocal() throws RemoteException;
    double getTotalGlobal(String usuario) throws RemoteException;
    
    // Métodos auxiliares para el registro de donaciones
    void addDonacion(Donaciones donacion) throws RemoteException;
    ArrayList<Donaciones> getRegistro() throws RemoteException;
    
    // Métodos auxiliares para la consulta y modificación de los usuarios
    void addUsuario(String usuario) throws RemoteException;
    ArrayList<String> getUsuarios() throws RemoteException;
    ArrayList<String> getUsuarioLocales() throws RemoteException;
    ArrayList<String> getUsuarioGlobales() throws RemoteException;
    
    // Métodos auxiliares extra
    void incrementarTotal(double cantidad) throws RemoteException;
    void asignarReferencia(I_Donaciones ref)throws RemoteException;
    ArrayList<I_Donaciones> obtenerReplicas()throws RemoteException;
}