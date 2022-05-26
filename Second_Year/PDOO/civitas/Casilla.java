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

import java.util.ArrayList;
public class Casilla {
    private String nombre;
    private static int carcel;
    private float importe;
    private TipoCasilla tipo;
    private TituloPropiedad tituloPropiedad;
    private Sorpresa sorpresa;
    private MazoSorpresas mazo;
    
    
    Casilla(String nombre){
        init();
        this.nombre=nombre; 
        tipo=TipoCasilla.DESCANSO;
    }
    
    Casilla(TituloPropiedad titulo){
        init();
        this.tituloPropiedad=titulo;
        tipo=TipoCasilla.CALLE;
    }
    
    Casilla(float cantidad,String nombre){
        init();
        importe=cantidad;
        this.nombre=nombre;
        tipo=TipoCasilla.IMPUESTO; 
    }
    
    Casilla(int numCasillaCarcel,String nombre){
        init();
        carcel=numCasillaCarcel;
        this.nombre=nombre;
        tipo=TipoCasilla.JUEZ; 
    }
    
    Casilla(MazoSorpresas mazo,String nombre){
        init();
        this.mazo=mazo;
        this.nombre=nombre;
        tipo=TipoCasilla.SORPRESA;
    }
    
    
    private void init(){
        nombre="Casilla";
        carcel=4;
        importe=0;
        tipo=TipoCasilla.CALLE;
        tituloPropiedad=null;
        sorpresa=null;
        mazo=null; 
    }
     
    
    public String getNombre(){
        return nombre;
    }
    
    private void informe (int actual, ArrayList<Jugador> todos){
        Diario.getInstance().ocurreEvento("El jugador "+todos.get(actual).getNombre()+" ha caido en la casilla "+toString());
    }
    
    /*
    @Override
    public String toString(){
       String a=tipo.toString();
       String b=Integer.toString(carcel);
       String c=Float.toString(importe);
       String mensaje="nombre= "+nombre+"   carcel= "+b+"   importe= "+c+"   tipo= "+a+"   tituloPropiedad= "+tituloPropiedad.getNombre()+
                      "   sorpresa= "+sorpresa.toString();
       return mensaje;
    }
    
    */
    
 
    
    
    
    public boolean jugadorCorrecto(int actual, ArrayList<Jugador> todos){
        return actual<=todos.size();
    }

    @Override
    public String toString() {
        return "Casilla{" + "nombre=" + nombre + ", importe=" + importe + ", tipo=" + tipo + ", tituloPropiedad=" + tituloPropiedad + ", sorpresa=" + sorpresa + ", mazo=" + mazo + '}';
    }
    
    private void recibeJugador_impuesto(int actual, ArrayList<Jugador> todos){
        if(jugadorCorrecto(actual,todos)){
            informe(actual,todos);
            todos.get(actual).pagaImpuesto(importe);
        }      
    }
    
    private void recibeJugador_juez(int actual, ArrayList<Jugador> todos){
        if(jugadorCorrecto(actual,todos)){
             informe(actual,todos);
             todos.get(actual).encarcelar(carcel);
        }
    }
    
    TituloPropiedad getTituloPropiedad(){
        return tituloPropiedad;
    }
    
    
    
    private void recibeJugador_calle(int iactual, ArrayList<Jugador>todos){
        if(jugadorCorrecto(iactual,todos)){
            informe(iactual,todos);
            Jugador jugador=todos.get(iactual);
            
            if(!tituloPropiedad.tienePropietario())
                jugador.puedeComprarCasilla();
            else{
                tituloPropiedad.tramitarAlquiler(jugador);
                
                
            }
                
            
        }
    }
    
    private void recibeJugador_sorpresa(int iactual, ArrayList<Jugador>todos){
         if(jugadorCorrecto(iactual,todos)){
             Sorpresa sorpresa=mazo.siguiente();
             informe(iactual,todos);
             sorpresa.aplicarAJugador(iactual, todos);
         }
    }
    
    
    
    void recibeJugador(int iactual, ArrayList<Jugador>todos){
        
        switch(tipo){
            
            case CALLE:
                   
                this.recibeJugador_calle(iactual, todos);
            break;
            
            case IMPUESTO:
                this.recibeJugador_impuesto(iactual, todos);
                break;
                
            case JUEZ:
                this.recibeJugador_juez(iactual, todos);
                break;
                
            case SORPRESA:
                this.recibeJugador_sorpresa(iactual, todos);
                break;
                
            default:
                this.informe(iactual, todos);
        }
    }
    
    
    
}
