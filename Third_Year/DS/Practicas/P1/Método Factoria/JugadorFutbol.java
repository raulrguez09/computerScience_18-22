/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package DesignPatterns_FactoryMethod;

public class JugadorFutbol extends Jugador {
    private final String piernaBuena;
    private final int dorsal;

    public JugadorFutbol(String nombre, int edad, String pierna, int d){
        super(nombre,edad);
        this.piernaBuena = pierna;
        this.dorsal = d;
        this.tipoJugador = "Fútbol";
    }

}

