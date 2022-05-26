/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package DesignPatterns_FactoryMethod;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Random;

public class FactoriaBaloncesto implements FactoriaPistaJugador {
    private ArrayList<String> nombres = new ArrayList<String>(Arrays.asList("Jose","Juan","Pepe","Cristian","Angel","Santi","Fran","Raul"));
    private ArrayList<String> posicion = new ArrayList<String>(Arrays.asList("Base","Alero","Escolta","Pívot"));

    private static final FactoriaBaloncesto INSTANCE = new FactoriaBaloncesto();
    
    private FactoriaBaloncesto(){};

    public static FactoriaBaloncesto getInstance(){
        return INSTANCE;
    }
    
    @Override
    public Pista crearPistaPartido(int numeroJugadores) {
        PistaBaloncesto pista = new PistaBaloncesto(25,170);

        for(int i=0; i < numeroJugadores; i++){
            if(i%2 == 0)
                pista.apuntarseLocal(crearJugador());
            else
                pista.apuntarseVisitante(crearJugador());
        }
        return pista;
    }

    @Override
    public Jugador crearJugador() {
        Random rand = new Random();
        int a = rand.nextInt(nombres.size());
        int b = rand.nextInt(20) + 15;
        int c = rand.nextInt(posicion.size());
        int d = rand.nextInt(50) + 170;
        return new JugadorBaloncesto(nombres.get(a),b,posicion.get(c),d);
    }

}
