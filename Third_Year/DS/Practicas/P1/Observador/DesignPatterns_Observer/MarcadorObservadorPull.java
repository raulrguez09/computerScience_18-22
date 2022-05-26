/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package DesignPatterns_Observer;
import GUI.ventana;

import java.lang.System.Logger;
import java.lang.System.Logger.Level;
import java.util.Observable;
import java.util.Observer;

public class MarcadorObservadorPull extends Thread implements Observer {
    private int local;
    private int visitante;
    public MarcadorObservable vo;
    private ventana miVentana = ventana.getInstance();
    
    public MarcadorObservadorPull (MarcadorObservable o){
        this.vo = o;
    }
    
    public void conexionPull(){
        local = vo.getLocal();
        visitante = vo.getVisitante();
        
        miVentana.setPullLocal(String.valueOf(local));
        miVentana.setPullVisitante(String.valueOf(visitante));
    }
    
    public void update(Observable obs, Object obj){
    }
    
    @Override
    public void run(){
        while(true){
                conexionPull();
            try{
                Thread.sleep(3000);
            } catch (InterruptedException ex){
                //Logger.getLogger(MarcadorObservadorPull.class.getName()).log(Level.WARNING, null, ex);
            }
        }
    }
    
    public int getLocal(){
        return local;
    }
    
    public int getVisitante(){
        return visitante;
    }
}
