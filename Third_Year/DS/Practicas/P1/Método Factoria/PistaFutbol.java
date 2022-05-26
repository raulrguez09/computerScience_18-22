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
public class PistaFutbol extends Pista {
    private String type;

    public PistaFutbol (float tamanio,String t){
        super(tamanio);
        this.type = t;
        this.tipo = "Fútbol";
    }

}
