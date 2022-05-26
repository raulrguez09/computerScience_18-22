package DesignPatterns_Observer;
import GUI.ventana;

import java.util.ArrayList;
import java.util.Observer;
import java.util.Observable;

public class MarcadorObservadorPush implements Observer {
    private int local;
    private int visitante;
    public MarcadorObservable vo = null;
    private ventana miVentana = ventana.getInstance();

    public MarcadorObservadorPush( MarcadorObservable o ) {
        this.vo = o;
    }
    
    @Override
    public void update( Observable obs, Object obj) {
        if( obs == vo ){
            ArrayList<Integer> marcador = (ArrayList<Integer>) obj;
            local = marcador.get(0);
            visitante = marcador.get(1);            
        }
        
        miVentana.setPushLocal(String.valueOf(local));
        miVentana.setPushVisitante(String.valueOf(visitante));
    }
}

