/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package civitas;
import java.util.ArrayList;
import java.util.Collections;
/**
 *
 * @author Raul Rodriguez Perez
 */
public class CivitasJuego {
    private int indiceJugadorActual;
    private EstadosJuego estado;
    private Tablero tablero;
    private MazoSorpresas mazo;
    private GestorEstados gestorEstados;
    private ArrayList<Jugador> jugadores;
    private OperacionesJuego operacion;
    
    public CivitasJuego(ArrayList<String>nombres){
        jugadores=new ArrayList();
        for(int i=0;i<nombres.size();i++)
            jugadores.add(new Jugador(nombres.get(i)));
        
        gestorEstados=new GestorEstados();
        estado=gestorEstados.estadoInicial();
        indiceJugadorActual=Dado.getInstance().quienEmpieza(jugadores.size());
        mazo=new MazoSorpresas(false);
        inicializaTablero(mazo);
        inicializaMazoSorpresas(tablero);
        
    }
    
    
    private void inicializaTablero (MazoSorpresas mazo){
        tablero=new Tablero(4);
        this.mazo=mazo;
        tablero.añadeCasilla(new Casilla(new TituloPropiedad("San Xenxo",80, (float) 1.20,610,880,200)));
        tablero.añadeCasilla(new Casilla(mazo,"¡Sorpresaaaa!"));
        tablero.añadeJuez();
        tablero.añadeCasilla(new Casilla(new TituloPropiedad("Torre de Hercules",70, (float) 1.20,590,840,185)));
        
        tablero.añadeCasilla(new Casilla(new TituloPropiedad("Matadero",60, (float) 1.17,565,800,170)));
        
        tablero.añadeCasilla(new Casilla(mazo,"¡Sorpresaaaa!"));
        tablero.añadeCasilla(new Casilla(new TituloPropiedad("Los Rosales",110, (float) 1.29,680,1150,240)));
        tablero.añadeCasilla(new Casilla(new TituloPropiedad("Orzan",100, (float) 1.26,650,950,230)));
        tablero.añadeCasilla(new Casilla("Descanso"));
        tablero.añadeCasilla(new Casilla(new TituloPropiedad("Riazor",90, (float) 1.23,630,920,215)));
        tablero.añadeCasilla(new Casilla(mazo,"¡Sorpresaaaa!"));
        tablero.añadeCasilla(new Casilla(new TituloPropiedad("Calle Monte Alto",170, (float) 1.44,830,1650,310)));
        tablero.añadeCasilla(new Casilla(new TituloPropiedad("Mesoiro",140, (float) 1.37,770,1500,280)));
      
        tablero.añadeCasilla(new Casilla(new TituloPropiedad("Cuatro Caminos",130, (float) 1.34,740,1300,270)));
        tablero.añadeCasilla(new Casilla(mazo,"¡Sorpresaaaa!"));
        tablero.añadeCasilla(new Casilla(new TituloPropiedad("Calle Medio Ambiente",210, (float) 1.53,950,2200,360)));
        tablero.añadeCasilla(new Casilla(new TituloPropiedad("Calle Margarita Xirgú",200, (float) 1.5,920,2000,350)));
        tablero.añadeCasilla(new Casilla((float)1000.0,"Multa por mamadisimo"));
        tablero.añadeCasilla(new Casilla(new TituloPropiedad("Calle Ferrol",180, (float) 1.45,860,1850,320)));

        
    }
    
    
    private void inicializaMazoSorpresas(Tablero tablero){
        
        mazo.alMazo(new Sorpresa(TipoSorpresa.PAGARCOBRAR,500,"Cobra 500 euros porque eres el mejor"));
        mazo.alMazo(new Sorpresa(TipoSorpresa.PAGARCOBRAR,-500,"Pagas 500  por exceso de velocidad"));
        mazo.alMazo(new Sorpresa(TipoSorpresa.IRCASILLA,tablero,0,"Avanza hasta la casilla Salida"));
        mazo.alMazo(new Sorpresa(TipoSorpresa.IRCASILLA,tablero,4,"Vas a la carcel por chulo"));
        mazo.alMazo(new Sorpresa(TipoSorpresa.IRCASILLA,tablero,8,"Ve a la casilla de descanso"));
        mazo.alMazo(new Sorpresa(TipoSorpresa.PORCASAHOTEL,200,"Recibes 200 por cada casa y hotel "));
        mazo.alMazo(new Sorpresa(TipoSorpresa.PORCASAHOTEL,-200,"Pagas 200 por cada casa y hotel "));
        mazo.alMazo(new Sorpresa(TipoSorpresa.PORJUGADOR,200,"Recibes 200 por cada jugador "));
        mazo.alMazo(new Sorpresa(TipoSorpresa.PORJUGADOR,-200,"Pagas 200 a cada jugador "));
        mazo.alMazo(new Sorpresa(TipoSorpresa.SALIRCARCEL,mazo));
        mazo.alMazo(new Sorpresa(TipoSorpresa.IRCARCEL,mazo));
    }
    //EXAMEN
    public void ponerPiscina(int ip){
        jugadores.get(indiceJugadorActual).ponerPiscina(ip);
    }
    
    //FIN EXAMEN
    private void contabilizarPasosPorSalida (Jugador jugadorActual){
        if(tablero.getPorSalida()>0)
            jugadorActual.pasaPorSalida();
    }
    
    private void pasarTurno(){
        indiceJugadorActual++;
        if(  indiceJugadorActual==jugadores.size())
              indiceJugadorActual=0;
        
    }
    
    public void siguientePasoCompletado(OperacionesJuego operación){
        estado=gestorEstados.siguienteEstado(jugadores.get(indiceJugadorActual), estado, operación);
    }
    
    public boolean vender(int ip){
        return jugadores.get(indiceJugadorActual).vender(ip);
    }
    
    public boolean hipotecar(int ip){
        return jugadores.get(indiceJugadorActual).hipotecar(ip);
    }
    
    public boolean cancelarHipoteca(int ip){
        return jugadores.get(indiceJugadorActual).cancelarHipoteca(ip);
    }
    
    public boolean construirCasa(int ip){
        return jugadores.get(indiceJugadorActual).construirCasa(ip);
    }
    
    public boolean construirHotel(int ip){
        return jugadores.get(indiceJugadorActual).construirHotel(ip);
    }
    
    public boolean salirCarcelPagando(){
        return jugadores.get(indiceJugadorActual).salirCarcelPagando();
    }
    
    public boolean salirCarcelTirando(){
        return jugadores.get(indiceJugadorActual).salirCarcelTirando();
    }
    
    public boolean finalDelJuego(){
        Boolean ok=false;
        for(int i=0; i<jugadores.size();i++){
           if(jugadores.get(i).enBancarrota())
               ok=true;
        }
        return ok;
    }
    
    
   public ArrayList<Jugador> ranking(){
        ArrayList<Jugador> lista=jugadores;
        lista.sort((o1,o2) -> o1.compareTo(o2));
        Collections.reverse(lista);
        return lista;
   }
    
    public Casilla getCasillaActual(){
        return tablero.getCasilla(getJugadorActual().getNumCasillaActual());
    }
    
    public Jugador getJugadorActual(){
        return jugadores.get(indiceJugadorActual);
    }
    
    private void avanzaJugador(){
        Jugador jugadorActual=getJugadorActual();
        int posicionActual=jugadorActual.getNumCasillaActual();
        int tirada=Dado.getInstance().tirar();
        int posicionNueva=tablero.nuevaPosicion(posicionActual, tirada);
        Casilla casilla=tablero.getCasilla(posicionNueva);
        this.contabilizarPasosPorSalida(jugadorActual);
        jugadorActual.moverACasilla(posicionNueva);
        casilla.recibeJugador(indiceJugadorActual, jugadores);
        this.contabilizarPasosPorSalida(jugadorActual);
    }
    
    
    public OperacionesJuego siguientePaso(){
        Jugador jugadorActual=jugadores.get(indiceJugadorActual);
        OperacionesJuego operacion=gestorEstados.operacionesPermitidas(jugadorActual, estado);
        if(operacion==OperacionesJuego.PASARTURNO){
            this.pasarTurno();
            this.siguientePasoCompletado(operacion);
        }
        else if(operacion==OperacionesJuego.AVANZAR){
            this.avanzaJugador();
            this.siguientePasoCompletado(operacion);
        }
        
        return operacion;
    }
    
    
    public boolean comprar(){
        Jugador jugadorActual=jugadores.get(indiceJugadorActual);
        int numCasillaActual=jugadorActual.getNumCasillaActual();
        Casilla casilla=tablero.getCasilla(numCasillaActual);
        TituloPropiedad titulo=casilla.getTituloPropiedad();
        boolean res=jugadorActual.comprar(titulo);
        return res;
    }
    
    
     public String infoJugadorTexto(){
        return jugadores.get(indiceJugadorActual).toString();
    }
    
    
    
}
