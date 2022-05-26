/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package juegoTexto;

import civitas.CivitasJuego;
import civitas.Dado;
import java.util.ArrayList;
/**
 *
 * @author Raul Rodriguez Perez
 */
public class TestP2 {
   public static void main6(){
       VistaTextual vistatext=new VistaTextual();
       ArrayList<String>nombres =new ArrayList();
       nombres.add("Jose");
       nombres.add("Otto");
       nombres.add("Mario");
       nombres.add("Claudia");
       Dado.getInstance().setDebug(Boolean.TRUE);
       CivitasJuego juego=new CivitasJuego(nombres);
       
       Controlador contr=new Controlador(juego,vistatext);
       
       contr.juega();
       
       
       
   }
}
