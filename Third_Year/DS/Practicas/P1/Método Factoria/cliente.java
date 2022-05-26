/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package DesignPatterns_FactoryMethod;

public class cliente {

    public static void main(String[] args) {
        FactoriaFutbol ff = FactoriaFutbol.getInstance();
        FactoriaBaloncesto fb = FactoriaBaloncesto.getInstance();

        ff.crearPistaPartido(22).start();
        fb.crearPistaPartido(10).start();
    }
    
}
