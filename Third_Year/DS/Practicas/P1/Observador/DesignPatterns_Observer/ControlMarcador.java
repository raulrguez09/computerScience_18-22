package DesignPatterns_Observer;

import java.util.*;
import GUI.ventana;
import java.lang.System.Logger;
import java.lang.System.Logger.Level;

public class ControlMarcador extends Thread {
    MarcadorObservable vo = null; //sujeto observable
    MarcadorObservadorPush mo = null; //Push -> suscrito
    MarcadorObservadorPull po = null; //Pull -> no suscrito
    MarcadorObservadorMod mod = null; //Mod -> suscrito modificador
    MarcadorObservadorGrafica gr = null; //gr -> grafica
    ventana miVentana = ventana.getInstance();
    
    // Constructor de la clase que nos permite crear los objetos de
    // observador y observable
    public ControlMarcador() {
        int puntos[] = {0,0};
        this.vo = new MarcadorObservable();
        this.mo = new MarcadorObservadorPush( vo );
        this.po = new MarcadorObservadorPull( vo );
        this.mod = new MarcadorObservadorMod( vo );
        this.gr = new MarcadorObservadorGrafica( vo );
        
        vo.addObserver(mod);
        vo.addObserver(gr);
        vo.addObserver(mo);
        miVentana.setVisible(true);
    }
    
    @Override
    public void run(){
        Random rnd = new Random();
        int local = 0, visitante = 0, i = 0;
        ArrayList<Integer> vec = new ArrayList<Integer>();
        vec.add(0);
        vec.add(0);
        //po.start();
        while(true){
            if(getId() == 11){
                local = rnd.nextInt(10);
                visitante = rnd.nextInt(10);
            }
            
            
        try{
            Thread.sleep(1000);
        } catch(InterruptedException ex){
            // Logger.getLogger(ControlValor.class.getName());
        }
        
            vec.set(0, local);
            vec.set(1, visitante);
            this.vo.setMarcador(vec);
            i++;
            
            if(i%6 == 0){
                po.conexionPull();
            }
        }
    }
    
    public static void main(String[] args){
        ControlMarcador co = new ControlMarcador();

        co.run();
    }
    
}
