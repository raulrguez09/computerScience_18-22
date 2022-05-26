/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package civitas;

import java.util.ArrayList;
/**
 *
 * @author Raul Rodriguez Perez
 */
public class Jugador implements Comparable<Jugador>{
    protected static int CasasMax=4;
    protected static int CasasPorHotel=4;
    protected Boolean encarcelado;
    protected static int HotelesMax=4;
    private String nombre;
    private int numCasillaActual;
    protected static float PasoPorSalida=1000;
    protected static float PrecioLibertad=200;
    private Boolean puedeComprar;
    private float saldo;
    static float SaldoInicial=7500;
    private ArrayList<TituloPropiedad> propiedades;
    private Sorpresa salvoconducto;
    
    
    public Jugador(String n){
        nombre=n;
        encarcelado=false;
        numCasillaActual=0;
        puedeComprar=true;
        saldo=7500;
        propiedades=new ArrayList<>();
        salvoconducto=null;
             
    }
    
    
    
    protected Jugador(Jugador otro){
       this(otro.nombre); 
    }

    @Override
    public String toString() {
        return "Jugador{" + "encarcelado=" + encarcelado + ", nombre=" + nombre + ", numCasillaActual=" + numCasillaActual + ", puedeComprar=" + puedeComprar + ", saldo=" + saldo + ", propiedades=" + propiedades.toString() + ", salvoconducto=" + salvoconducto + '}'+"\n";
    }
    
    
    
  /*   
    @Override
   public String toString(){
       String a=Boolean.toString(encarcelado);
       String b=Integer.toString(numCasillaActual);
       String c=Boolean.toString(puedeComprar);
       String d=Float.toString(saldo);
       String e=Float.toString(SaldoInicial);
       String f=salvoconducto.toString();
       String mensaje1;
       String mensaje2="Propiedades= ";
       
       
       mensaje1="Saldo inicial= "+e+"  saldo actual= "+d+"  encarcelado= "+a+"  numero de la casilla actual= "+b+"  puede comprar= "+c+"  sorpresa= "+f;
       
       for(int i=0;i<propiedades.size();i++)
           mensaje2=mensaje2+propiedades.get(i).getNombre();
       
       
       return mensaje1+mensaje2;
   }
    */
    //EXAMEN
    public Boolean tieneHotel(){
        Boolean tiene = false;
        for(int i = 0;i < propiedades.size ();i++){
            if(propiedades.get(i).getNumHoteles() > 0)
                tiene = true;
        }
        return tiene;
    }
    
    public Boolean ponerPiscina(int ip){
        Boolean result=false;
         if(encarcelado)
           return result;
         if(this.existeLaPropiedad(ip)){
           TituloPropiedad propiedad=propiedades.get(ip);
           if(this.tieneHotel())
               propiedad.ponerPiscina();
           result = true;
               Diario.getInstance().ocurreEvento("El jugador "+nombre+" construye piscina en la propiedad "+propiedades.get(ip).getNombre());
         }
         return result;
    }
    
    public ArrayList<String> getNombrePropiedadesConHotel(){
       ArrayList<String> nombres = new ArrayList<>();
       
       for(int i=0;i<propiedades.size();i++){
           if(propiedades.get(i).getNumHoteles() > 0)
            nombres.add(propiedades.get(i).getNombre());
       }
       return nombres;
       
    }
    //FIN EXAMEN
    
    public Boolean isEncarcelado(){
        return encarcelado;
    }
    
    Boolean modificarSaldo(float cantidad){
        
        saldo=saldo+cantidad;
        Diario.getInstance().ocurreEvento("Se ha modificado el sueldo del jugador "+nombre);
        return true;
    }
    
    
    
    Boolean paga(float cantidad){
        Boolean ok;
        ok=modificarSaldo(cantidad*-1);
        return ok; 
    }
    
    Boolean recibe(float cantidad){
        if(encarcelado)
            return false;
        
        else {
           Boolean ok=modificarSaldo(cantidad); 
           return ok;
        }
    }
    
    
    
   Boolean pagaAlquiler(float cantidad){
        if(encarcelado)
           return false;
       
       else
           return paga(cantidad);
   }
   
   
   Boolean pagaImpuesto(float cantidad){
       if(encarcelado)
           return false;
       
       else
           return paga(cantidad);
                    
   }
   
   public String getNombre(){
       return nombre;
   }
   
   Boolean tieneSalvoconducto(){
       return salvoconducto!=null;
   }
   
   private void perderSalvoconducto (){
       salvoconducto.usada();
       salvoconducto=null;
   }
   
   protected Boolean debeSerEncarcelado(){
      if(isEncarcelado())
           return false;
       else
           if(!tieneSalvoconducto())
               return true;
           else{
               perderSalvoconducto();
               Diario.getInstance().ocurreEvento("El jugador "+nombre +" se libra de la cárcel");
               return false;
           }
           
   }
   
   
   Boolean encarcelar(int numCasillaCarcel){
       if(debeSerEncarcelado())  
           moverACasilla(numCasillaCarcel);
           encarcelado=true;
           Diario.getInstance().ocurreEvento("Se ha encarcelado al jugador "+nombre);
           return encarcelado;
   }
   
   Boolean moverACasilla(int numCasilla){
       if(encarcelado)
           return false;
       else
           numCasillaActual=numCasilla;
           puedeComprar=false; 
           Diario.getInstance().ocurreEvento("El jugador "+ nombre + " se ha movido a la casilla "+Float.toString(numCasillaActual));
           return true;
   }
   
   int getNumCasillaActual(){
       return numCasillaActual;
   }
   
   int cantidadCasasHoteles(){
       int cont=0;
       for(int i=0; i<propiedades.size();i++){
           cont+=propiedades.get(i).cantidadCasasHoteles();
       }
       return cont;
   }
   
   
   boolean obtenerSalvoconducto(Sorpresa s){
       if(encarcelado)
           return false;
       else{
           salvoconducto=s;
           return true;     
       }
  }
   
   boolean puedeComprarCasilla(){
       puedeComprar = !encarcelado;
      
      return puedeComprar;   
   }
   
   private boolean puedoGastar (float precio){
       if(encarcelado)
           return false;
       else
           return saldo>=precio;
   }
   
   private Boolean existeLaPropiedad(int ip){
       return ip<=propiedades.size();
   }
   
   boolean vender(int ip){
       if(encarcelado)
           return false;
      else{
           if(existeLaPropiedad(ip)){
               Boolean ok=propiedades.get(ip).vender(this);
               if(ok){
                   Diario.getInstance().ocurreEvento("La propiedad "+propiedades.get(ip).getNombre()+" ha sido vendida por el jugador "+this.nombre);
                   propiedades.remove(ip);
                   return true;
               }
               else
                   return false;
           }
           else
               return false;
       }
   }
   
   boolean tieneAlgoQueGestionar(){
       return propiedades!=null;
   }
   
   private Boolean puedeSalirCarcelPagando(){
       return saldo>=PrecioLibertad;
   }
    
   
   boolean salirCarcelPagando(){
       if(encarcelado && puedeSalirCarcelPagando()){
           paga(PrecioLibertad);
           encarcelado=false;
           String a=Float.toString(PrecioLibertad);
           Diario.getInstance().ocurreEvento("El jugador "+nombre+" ha salido de la carcel pagando "+a+ " euros");
           return true;
       }
       else
           return false;
   }
   
   
   boolean salirCarcelTirando(){
       if(Dado.getInstance().salgoDeLaCarcel()){
           encarcelado=false;
           Diario.getInstance().ocurreEvento("El jugador "+nombre+" ha salido de la carcel mediante tirada");
           return true;
       }
       else
           return false;
   }
   
   
   boolean pasaPorSalida(){
       modificarSaldo(PasoPorSalida);
       String a=Float.toString(PasoPorSalida);
       Diario.getInstance().ocurreEvento("El jugador "+nombre+" ha recibido "+a+" por pasar por la casilla Salida");
       return true;
   }
   
   boolean enBancarrota(){
       return saldo<=0;
   }
   
   private int getCasasMax(){
       return CasasMax;
   }
   
   int getCasasPorHotel(){
       return CasasPorHotel;
   }
   
   private int getHotelesMax(){
       return HotelesMax;
   }
   
   private float getPrecioLibertad(){
       return PrecioLibertad;
   }
   
   private float getPremioPasoSalida(){
       return PasoPorSalida;
   }
   protected ArrayList<TituloPropiedad> getPropiedades(){
       return propiedades;
   }
   
   boolean getPuedeComprar(){
       return puedeComprar;
   }
   
   @Override
    public int compareTo(Jugador otro){

        return Float.compare(this.saldo, otro.saldo);
    }
    
    private boolean puedoEdificarCasa(TituloPropiedad propiedad){
        if(encarcelado)
            return false;
   
        if(propiedad.getNumCasas()<=CasasMax)
        return saldo>=propiedad.getPrecioEdificar();
        else
            return false;
          
    }
    
   
   private boolean puedoEdificarHotel(TituloPropiedad propiedad){
       if(encarcelado)
           return false;
       else{
           if(propiedad.getNumHoteles()<=HotelesMax && propiedad.getNumCasas()==4)
               return saldo>=propiedad.getPrecioEdificar();
            else
               return false;      
       }
           
   }
   
   
   boolean cancelarHipoteca(int ip){
       Boolean result=false;
        if(encarcelado)
            return result;
       
        if(existeLaPropiedad(ip)){
            TituloPropiedad propiedad=propiedades.get(ip);
            float cantidad=propiedad.getImporteCancelarHipoteca();
            boolean puedoGastar=puedoGastar(cantidad);
            
            if(puedoGastar){
                result=propiedad.cancelarHipoteca(this);
                
                
                
                if(result)
                  Diario.getInstance().ocurreEvento("El jugador "+nombre+" cancela la hipoteca de la propiedad"+ip);
                
            }
        }
        
        return result;
       
       
   }
   
   
   boolean comprar(TituloPropiedad titulo){
       boolean result=false;
       if(encarcelado)
           return result;
       if(puedeComprar){
           float precio=titulo.getPrecioCompra();
           if(puedoGastar(precio)){
              result=titulo.Comprar(this);
              if(result){
                  propiedades.add(titulo);
                  Diario.getInstance().ocurreEvento("El jugador"+nombre+"compra la propiedad"+titulo.toString());
              }
              puedeComprar=false;
           }
       }
       
       return result;
       
   }
   
   
   boolean construirHotel(int ip){
       boolean result=false;
       if(encarcelado)
           return result;
       
       if(this.existeLaPropiedad(ip)){
           TituloPropiedad propiedad=propiedades.get(ip);
           boolean puedoEdificarHotel=this.puedoEdificarHotel(propiedad);
           float precio=propiedad.getPrecioEdificar();
           if(puedoGastar(precio) && propiedad.getNumHoteles()<this.getHotelesMax() && propiedad.getNumCasas()>=this.getCasasPorHotel()){
               puedoEdificarHotel=true;
           }
           if(puedoEdificarHotel){
               result=propiedad.construirHotel(this);
               propiedad.derruirCasas(CasasPorHotel, this);
               Diario.getInstance().ocurreEvento("El jugador "+nombre+" construye hotel en la propiedad "+propiedades.get(ip).getNombre());
           }
       }
       
       
      return result; 
   }
   
   
   
   boolean hipotecar(int ip){
       boolean result=false;
       if(encarcelado)
           return result;
       
       if(this.existeLaPropiedad(ip)){
           TituloPropiedad propiedad=propiedades.get(ip);
           result=propiedad.hipotecar(this);
       }
       
       if(result){
           Diario.getInstance().ocurreEvento("El jugador"+nombre+"hipoteca la propiedad"+ip);
       }
       return result;
   }
   
   
   
    boolean construirCasa(int ip){
       boolean result=false;
       boolean puedoEdificarCasa=false;
       
       if(encarcelado)
           return result;
       else{
           boolean existe=this.existeLaPropiedad(ip);
           if(existe){
               TituloPropiedad propiedad=propiedades.get(ip);
               puedoEdificarCasa=this.puedoEdificarCasa(propiedad);
               if(puedoEdificarCasa){
                   result=propiedad.construirCasa(this);
                   if(result)
                       Diario.getInstance().ocurreEvento("El jugador "+nombre+" construye casa en la propiedad "+propiedades.get(ip).getNombre());
               }
              
           }
       }
       return result;
       
   }
    
    public ArrayList<String> getNombrePropiedades(){
       ArrayList<String> nombres = new ArrayList<>();
       
       for(int i=0;i<propiedades.size();i++)
           nombres.add(propiedades.get(i).getNombre());
       
       return nombres;
       
    }
    
   
    
   
  
   
}    
   
   
   

