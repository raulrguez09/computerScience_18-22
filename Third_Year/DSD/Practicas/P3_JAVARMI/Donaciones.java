
import java.io.Serializable;

public class Donaciones implements Serializable{
    public String usuario;
    public double donacion;
    
    Donaciones(String user, double cant){
        this.usuario = user;
        this.donacion = cant;
    }
    
    public String getUser()
    {
        return this.usuario;
    }
    
    public void setUser(String u)
    {
        this.usuario = u;
    }
    
    public double getDonacion()
    {
        return this.donacion;
    }
    
    public void setDonacion(double d)
    {
        this.donacion = d;
    }
}
