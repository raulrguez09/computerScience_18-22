/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package DesignPatterns_Observer;
import GUI.ventana;

import java.util.ArrayList;
import java.util.Observer;
import java.util.Observable;

public class MarcadorObservadorMod implements Observer {
    private int local;
    private int visitante;
    public MarcadorObservable vo = null;
    private ventana miVentana = ventana.getInstance();

    public MarcadorObservadorMod( MarcadorObservable o ) {
        this.vo = o;
    }
    
    @Override
    public void update( Observable obs, Object obj) {
        if(miVentana.reiniciar){
            vo.setLocal(0);
        }
        else{
            if( obs == vo ){
                ArrayList<Integer> marcador = (ArrayList<Integer>) obj;
                local = marcador.get(0);
                visitante = marcador.get(1);            
            }

            miVentana.setModLocal(String.valueOf(vo.getLocal()));
            miVentana.setModVisitante(String.valueOf(visitante));
        }
        
    }
}
