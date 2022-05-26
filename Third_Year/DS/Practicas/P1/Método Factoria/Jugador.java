/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package DesignPatterns_FactoryMethod;

import java.util.*;
import java.util.logging.Level;
import java.util.logging.Logger;

public abstract class Jugador extends Thread {
    protected String nombre;
    private int edad;
    protected String tipoJugador;
    private int duracionJ = 5;
    private static int duracionDefecto = 5;
    
    public Jugador(String nombre, int edad){
        this.nombre = nombre;
        this.edad = edad;
    }

    public void setLesion(int tiempo) {
        this.duracionJ = tiempo;
    }
    
    public void salir(String msj) {
        System.out.println(this.nombre+"("+getId()+")"+msj);
    }
    
    @Override
    public void run(){
            try{
                Thread.sleep(this.duracionJ*1000);     
            } catch(InterruptedException ex){
                Logger.getLogger(Jugador.class.getName()).log(Level.SEVERE, null, ex);
            }
            if(this.duracionJ == this.duracionDefecto)
                salir(" se va del partido "+this.tipoJugador+" porque ha finalizado");
            else
                salir(" se lesiona y se sale antes del partido de "+this.tipoJugador);
    }
        
}

