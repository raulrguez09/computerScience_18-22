/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package DesignPatterns_FactoryMethod;

public interface FactoriaPistaJugador {
    Pista crearPistaPartido(int numeroJugadores);
    Jugador crearJugador();
}
