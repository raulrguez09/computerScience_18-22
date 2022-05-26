/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package DesignPatterns_FactoryMethod;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Random;

public class FactoriaFutbol implements FactoriaPistaJugador {
    private ArrayList<String> nombres = new ArrayList<String>(Arrays.asList("Jose","Juan","Pepe","Cristian","Angel","Santi","Fran","Raul"));
    private ArrayList<String> pierna = new ArrayList<String>(Arrays.asList("Derecha","Izquierda"));

    private static final FactoriaFutbol INSTANCE = new FactoriaFutbol();

    private FactoriaFutbol(){}
    
    public static FactoriaFutbol getInstance() {
        return INSTANCE;
    }

    @Override
    public PistaFutbol crearPistaPartido(int numeroJugadores){
        PistaFutbol pista = new PistaFutbol(25,"11");

        for(int i=0; i< numeroJugadores; i++){
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
        int c = rand.nextInt(2);
        int d = rand.nextInt(99) + 1;
        return new JugadorFutbol(nombres.get(a),b,pierna.get(c),d);
    }
}
