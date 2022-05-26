/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package DesignPatterns_Observer;
import GUI.ventana;
import java.util.ArrayList;
import java.util.Observable;


public class MarcadorObservable extends Observable {
    private ArrayList<Integer> puntos;
    private ventana miVentana = ventana.getInstance();
    
    
    public MarcadorObservable(){
        super();
        this.puntos = new ArrayList<Integer>();
        puntos.add(0, 0);
        puntos.add(1, 0);
    }

    
    public void setMarcador(ArrayList<Integer> nValor) {
       int local = puntos.get(0) + nValor.get(0);
       int visitante = puntos.get(1) + nValor.get(1);
       this.puntos.set(0, local);
       this.puntos.set(1, visitante);
              
       miVentana.setObservableLocal(String.valueOf(puntos.get(0)));
       miVentana.setObservableVisitante(String.valueOf(puntos.get(1)));
       
       setChanged();
       ArrayList<Integer> obj = new ArrayList<Integer>();
       obj.add(puntos.get(0));
       obj.add(puntos.get(1));
       notifyObservers(obj);
    }


    public int getLocal() {
       return( this.puntos.get(0) );
    }
    
    public int getVisitante() {
       return( this.puntos.get(1) );
    }

    public void setLocal(int n){
       miVentana.reiniciar = false;
       this.puntos.set(0, n);
        
       miVentana.setObservableLocal(String.valueOf(puntos.get(0)));
       miVentana.setObservableVisitante(String.valueOf(puntos.get(1)));
       
       setChanged();
       ArrayList<Integer> obj = new ArrayList<Integer>();
       obj.add(puntos.get(0));
       obj.add(puntos.get(1));
       notifyObservers(obj);
    }
    
}

