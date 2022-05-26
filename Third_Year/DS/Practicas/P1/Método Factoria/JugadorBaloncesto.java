/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package DesignPatterns_FactoryMethod;

/**
 *
 * @author raulrguez
 */
public class JugadorBaloncesto extends Jugador{
    private final String posicion;
    private final float altura;

    public JugadorBaloncesto(String nombre, int edad, String pos, float h){
        super(nombre,edad);
        this.posicion = pos;
        this.altura = h;
        this.tipoJugador = "Baloncesto";
    }
 
}
