/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package DesignPatterns_FactoryMethod;
import java.util.*;
import java.util.logging.Level;
import java.util.logging.Logger;

public abstract class Pista extends Thread {
    private ArrayList<Jugador> equipo_local = new ArrayList();
    private ArrayList<Jugador> equipo_visitante = new ArrayList();
    private float tamanio;
    private int minutos = 4;
    public Jugador participa;
    protected String tipo;
    
    public Pista(float tamanio){
        this.tamanio = tamanio;
    }
    
    public void apuntarseLocal(Jugador jug){
        equipo_local.add(jug);
    }
    
    public void apuntarseVisitante(Jugador jug){
        equipo_visitante.add(jug);
    }
    
    
    public void comenzarPartido(){
        for(Jugador j : equipo_local){
            j.start();
            System.out.println("El jugador de " + j.tipoJugador + " " +j.nombre + " empieza a jugar.(" + j.getId() + ")");
        }
        for(Jugador j : equipo_visitante){
            j.start();
            System.out.println("El jugador de " + j.tipoJugador + " " +j.nombre + " empieza a jugar.(" + j.getId() + ")");
        }
    }
    

    @Override
    public void run(){
        Random rand = new Random();
        int lesionesLocal = (int) (equipo_local.size() * 0.4);
        int lesionesVisitante = (int) (equipo_visitante.size() * 0.2);
        int tiempoLesion = rand.nextInt(this.minutos);

        for(int i=0; i<lesionesLocal; i++) {
            equipo_local.get(rand.nextInt(equipo_local.size())).setLesion(tiempoLesion);
        }
        for(int i=0; i<lesionesVisitante; i++) {
            equipo_visitante.get(rand.nextInt(equipo_visitante.size())).setLesion(tiempoLesion);
        }
        System.out.println("El partido de "+this.tipo+" ha empezado");
        comenzarPartido();

        try{
            Thread.sleep(minutos*1000);
        } catch(InterruptedException ex){
            Logger.getLogger(Pista.class.getName()).log(Level.SEVERE, null, ex);
      }
      System.out.println("El partido de "+this.tipo+" ha finalizado");
    }
    
}
