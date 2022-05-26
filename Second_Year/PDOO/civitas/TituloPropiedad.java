/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package civitas;

/**
 *
 * @author Raul Rodriguez Perez
 */
public class TituloPropiedad {
    
    private float alquilerBase;
    private static float factorInteresesHipoteca=(float) 1.1;
    private float factorRevalorizacion;
    private float hipotecaBase;
    private Boolean hipotecado;
    private String nombre;
    private int numCasas;
    private int numHoteles;
    private float precioCompra;
    private float precioEdificar;
    private Jugador propietario;
    //EXAMEN
    public Boolean piscinas;
    //FIN EXAMEN
    
    
    public TituloPropiedad(String Nombre,float PrecioBaseAlquiler,float factorReva,float PrecioBaseHipoteca ,float PrecioCompra, float PrecioPorEdificar){
        
       nombre=Nombre;
       alquilerBase=PrecioBaseAlquiler;
       factorRevalorizacion=factorReva;
       hipotecaBase=PrecioBaseHipoteca;
       precioCompra=PrecioCompra;
       precioEdificar=PrecioPorEdificar;
       propietario=null;
       numCasas=0;
       numHoteles=0;
       hipotecado=false;
       //EXAMEN
        piscinas = false;
        //FIN EXAMEN
        }
    
    @Override
    public String toString(){
        String aB=Float.toString(alquilerBase);
        String fI =Float.toString(factorInteresesHipoteca);
        String fR=Float.toString(factorRevalorizacion);
        String hB=Float.toString(hipotecaBase);
        String hip=Boolean.toString(hipotecado);
        String nC=Integer.toString(numCasas);
        String nH=Integer.toString(numHoteles);
        String pC=Float.toString(precioCompra);
        String pD=Float.toString(precioEdificar);
        //EXAMEN
        String pis=Boolean.toString(piscinas);
        
        String todo=nombre+", "+ aB + ", "+fI + ", "+fR + ", " +hB +", "+hip+", "+nC+", "+", "+nH+", "+pC+", "+pD+", "+pis+", ";
        //FIN EXAMEN
        return todo;
    }


    /*
    @Override
    public String toString() {
        return "TituloPropiedad{" + "alquilerBase=" + alquilerBase + ", factorRevalorizacion=" + factorRevalorizacion + ", hipotecaBase=" + hipotecaBase + ", hipotecado=" + hipotecado + ", nombre=" + nombre + ", numCasas=" + numCasas + ", numHoteles=" + numHoteles + ", precioCompra=" + precioCompra + ", precioEdificar=" + precioEdificar + ", propietario=" + propietario + '}';
    }
    */
    //EXAMEN
    public void ponerPiscina(){
    
        propietario.paga(1000);
        piscinas = true;
        
    }
    //FIN EXAMEN   
    
      private Boolean PropietarioEncarcelado(){
        
          return !(!propietario.encarcelado||!tienePropietario());
      }
    
    public float getPrecioAlquiler(){
        float var;
        if(hipotecado||PropietarioEncarcelado())
            var=0;
        else
            var= (float) (alquilerBase *(1+(numCasas*0.5)+(numHoteles*2.5)));
        
        return var;       
    }
    
    Boolean hipotecar (Jugador jugador){
         if(!hipotecado && esEsteElPropietario(jugador)){
            propietario.recibe(getImporteHipoteca());
            hipotecado=true;
            return true;
         }
         else
             return false;
    }
    
    float getImporteHipoteca(){
        float CantidadRecibida;
        CantidadRecibida=(float) (hipotecaBase*(1+(numCasas*0.5)+(numHoteles*2.5)));
        return CantidadRecibida;
    }
    
    
   float getImporteCancelarHipoteca(){
       return  this.getImporteHipoteca()*factorInteresesHipoteca;
    }
    
    
    public Boolean esEsteElPropietario(Jugador jugador){
        return propietario==jugador;
    }
            
    Boolean cancelarHipoteca(Jugador jugador){
        if(hipotecado && esEsteElPropietario(jugador)){
             propietario.paga(getImporteCancelarHipoteca());
             hipotecado=false;
             return true;
        }
        else
            return false;
    }
    
    
    Boolean tienePropietario(){
        return propietario!=null;
    }
    
    
    void tramitarAlquiler(Jugador jugador){
        if(!esEsteElPropietario(jugador) && tienePropietario())
            jugador.pagaAlquiler(getPrecioAlquiler());
            propietario.recibe(getPrecioAlquiler());
    }
    
    int cantidadCasasHoteles(){
        return numCasas+numHoteles;
    }
    
    Boolean derruirCasas(int n, Jugador jugador){
        if(esEsteElPropietario(jugador) && numCasas>=n){
            numCasas=numCasas-n;
            return true;
        }
        else
            return false;
    }
    
    private float getPrecioVenta(){
        return precioCompra+(numCasas+5*numHoteles)*precioEdificar*factorRevalorizacion;
    }
    
    Boolean construirCasa(Jugador jugador){
        Boolean ok=false;
        if(esEsteElPropietario(jugador)){
            ok=true;
            jugador.paga(precioEdificar);
            numCasas++;
        }
        
        return ok;
    }
    
    Boolean construirHotel(Jugador jugador){
         Boolean ok=false;
        if(esEsteElPropietario(jugador)){
            ok=true;
            jugador.paga(precioEdificar*5);
            numHoteles++;
        }
        
        return ok;
    }
    
    Boolean Comprar(Jugador jugador){
        if(tienePropietario())
            return false;
        else{
            propietario=jugador;
            propietario.paga(precioCompra);
            return true;
        }
    }
    
    
    
    
    void actualizaPropietarioPorConversion(Jugador jugador){
        propietario=jugador;
    }
    
    Boolean vender(Jugador jugador){
        if(esEsteElPropietario(jugador)){
            propietario.recibe(getPrecioVenta());
            propietario=null;
            numCasas=0;
            numHoteles=0;
            return true;
        }
        else
            return false;
    }
    
    public Boolean getHipotecado(){
        return hipotecado;
    }
    
    String getNombre(){
        return nombre;
    }
    
    int getNumCasas(){
        return numCasas;
    }
    
    int getNumHoteles(){
        return numHoteles;
    }
    
    float getPrecioCompra(){
        return precioCompra;
    }
    
    float getPrecioEdificar(){
        return precioEdificar;
    }
    
    Jugador getPropietario(){
        return propietario;
    } 
}
    