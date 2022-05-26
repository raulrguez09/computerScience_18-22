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
public class Sorpresa {
    private String texto;
    private int valor;
    private Tablero tablero;
    private MazoSorpresas mazo;
    private TipoSorpresa tipo;
    
    
    private void init(){
        valor=-1;
        mazo=null;
        tablero=null;
    }
    
    Sorpresa(TipoSorpresa tipo,Tablero tablero){
        init();
        this.tablero=tablero;
        this.tipo=TipoSorpresa.IRCARCEL;      
    }
    
    Sorpresa(TipoSorpresa tipo,Tablero tablero,int valor,String texto){
        init();
        this.tipo=TipoSorpresa.IRCASILLA;
        this.tablero=tablero;
        this.valor=valor;
        this.texto=texto;
                
    }
    
    Sorpresa(TipoSorpresa tipo,MazoSorpresas mazo){
        init();
        this.tipo=TipoSorpresa.SALIRCARCEL;
        this.mazo=mazo;
    }
    
    Sorpresa(TipoSorpresa tipo,int valor,String texto){
        init();
        this.tipo=tipo;
        this.valor=valor;
        this.texto=texto;
        
    }
    
    public boolean jugadorCorrecto (int actual, ArrayList<Jugador> todos){
       return actual<=todos.size();
   } 
    
    private void informe (int actual, ArrayList<Jugador> todos){
        String a=tipo.toString();
        String mensaje="Se esta aplicando una sopresa " + a + " al jugador "+todos.get(actual).getNombre();
        Diario.getInstance().ocurreEvento(mensaje);
    }
    
    void aplicarAJugador(int actual, ArrayList<Jugador> todos){
         if(tipo==TipoSorpresa.IRCARCEL)
             aplicarAJugador_irCarcel(actual,todos);
         if(tipo==TipoSorpresa.IRCASILLA)
             aplicarAJugador_irACasilla(actual,todos);
         if(tipo==TipoSorpresa.PAGARCOBRAR)
             aplicarAJugador_pagarCobrar(actual,todos);
         if(tipo==TipoSorpresa.PORCASAHOTEL)
             aplicarAJugador_porCasaHotel(actual,todos);
         if(tipo==TipoSorpresa.PORJUGADOR)
            aplicarAJugador_porJugador(actual,todos);
         if(tipo==TipoSorpresa.SALIRCARCEL)
             aplicarAJugador_salirCarcel(actual,todos);
             
    }
   
    void usada(){
        if(tipo==TipoSorpresa.SALIRCARCEL){
           mazo.habilitarCartaEspecial(tipo);
        }
            
    }
    
    private void aplicarAJugador_irCarcel (int actual, ArrayList<Jugador> todos){
        if(jugadorCorrecto(actual,todos)){
            informe(actual,todos);
            todos.get(actual).encarcelar(tablero.getCarcel());
            }
        }
    
    
    private void aplicarAJugador_irACasilla(int actual, ArrayList<Jugador> todos){
         if(jugadorCorrecto(actual,todos)){
             informe(actual,todos);
             int a=todos.get(actual).getNumCasillaActual();
             int tirada=tablero.calcularTirada(a,valor);
             int nuevaPos=tablero.nuevaPosicion(a,tirada);
             todos.get(actual).moverACasilla(nuevaPos);
             tablero.getCasilla(nuevaPos).recibeJugador(actual, todos);
         }
        
        }
    
    private void aplicarAJugador_pagarCobrar(int actual,ArrayList<Jugador>todos){ 
            if(jugadorCorrecto(actual,todos)){
                informe(actual,todos);
                todos.get(actual).modificarSaldo(valor);
            }
        }
    
    
    private void aplicarAJugador_porCasaHotel(int actual,ArrayList<Jugador>todos){
         if(jugadorCorrecto(actual,todos)){
             informe(actual,todos);
              todos.get(actual).modificarSaldo(valor*todos.get(actual).cantidadCasasHoteles());
         }
    }
    
    private void aplicarAJugador_porJugador(int actual,ArrayList<Jugador>todos){
         if(jugadorCorrecto(actual,todos)){
            informe(actual,todos);
             Sorpresa a = new Sorpresa(TipoSorpresa.PAGARCOBRAR,valor*-1,"Pagan todos los jugadores menos el no afectado ");
             for(int i=0;i<todos.size();i++){
                 if(i!=actual)
                    a.aplicarAJugador_pagarCobrar(i, todos);
                }
             
             Sorpresa b=new Sorpresa(TipoSorpresa.PAGARCOBRAR,valor*(todos.size()-1),"Recibe dinero de todos los jugadores");
                b.aplicarAJugador_pagarCobrar(actual, todos);
             }
        }
    
    
    private void aplicarAJugador_salirCarcel(int actual,ArrayList<Jugador>todos){
         if(jugadorCorrecto(actual,todos)){
            informe(actual,todos);
            Boolean ok=false;
            for(int i=0; i<todos.size();i++)
              if(todos.get(i).tieneSalvoconducto())
                  ok=true;
            
              if(!ok){
                  todos.get(actual).obtenerSalvoconducto(this);
                  salirDelMazo();
              }
         }
    }
     
    void salirDelMazo(){
        if(tipo==TipoSorpresa.SALIRCARCEL)
            mazo.inhabilitarCartaEspecial(this);
    }
   
    /*
    @Override
    public String toString(){
        String a=tipo.toString();
        return a;
   }

    */

    @Override
    public String toString() {
        return "Sorpresa{" + "texto=" + texto + ", valor=" + valor + ", tablero=" + tablero + ", mazo=" + mazo + ", tipo=" + tipo + '}';
    }
    
    
    
    
    
    
    }


