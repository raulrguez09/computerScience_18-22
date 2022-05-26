/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package civitas;

import java.util.ArrayList;
import juegoTexto.Controlador;
import juegoTexto.VistaTextual;
/**
 *
 * @author Raul Rodriguez Perez
 */
public class TestP1 {
    
   static void main(){
       for(int i=0; i<100; i++)
           System.out.println  (Dado.getInstance().quienEmpieza(4));
       
     
    }
   
   static void main2(){
       
       Dado.getInstance().setDebug(false);
       for(int i=0; i<50; i++)
           
            System.out.println (Dado.getInstance().salgoDeLaCarcel());
   }
   
   static void main3(){
       System.out.println (EstadosJuego.DESPUES_AVANZAR);
   }
  /* 
   static void main4(){
       MazoSorpresas a=new MazoSorpresas();
       
       a.alMazo();
       a.alMazo(c);
       a.siguiente();
       a.inhabilitarCartaEspecial(c);
       a.habilitarCartaEspecial(c);
        System.out.println (Diario.getInstance().leerEvento());
        System.out.println (Diario.getInstance().leerEvento());  
    
   }
   */
   
   static void main5(){
       Tablero a=new Tablero(3);
       Casilla b=new Casilla("Josefina");
       Casilla c=new Casilla("Conchi");
       Casilla d=new Casilla("Marimar");
       Casilla e=new Casilla("Franco");
       
      
           a.añadeCasilla(b);
           a.añadeCasilla(c);    
           a.añadeCasilla(d);
           a.añadeCasilla(e);
           
           
   }
   
   static void main6(){
       VistaTextual vistatext=new VistaTextual();
       ArrayList<String>nombres =new ArrayList();
       nombres.add("Santi");
       nombres.add("Yoli");
       nombres.add("Alicia");
       nombres.add("PAPA");
       Dado.getInstance().setDebug(Boolean.TRUE);
       CivitasJuego juego=new CivitasJuego(nombres);
       
       Controlador contr=new Controlador(juego,vistatext);
       
       contr.juega();
       
       
       
   }
   
       
}
