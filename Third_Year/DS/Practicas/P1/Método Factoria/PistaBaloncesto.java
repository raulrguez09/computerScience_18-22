/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package DesignPatterns_FactoryMethod;


public class PistaBaloncesto extends Pista {
    private float alturaCanastas;

    public PistaBaloncesto (float tamanio,float alt){
        super(tamanio);
        this.alturaCanastas = alt;
        this.tipo = "Baloncesto";
    }

}
