/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package civitas;

import java.util.Random;

public class Dado {
    
    private Random random;
    private int ultimoResultado;
    private Boolean debug;
    private static final Dado instance=new Dado();
    private static int SalidaCarcel=5;
    
    private Dado(){
        random=new Random();
        ultimoResultado=1;
        debug=false;
    }
    
    public static Dado getInstance(){
        return instance;
    }
    
    int tirar(){
        if(!debug){
            ultimoResultado=1+random.nextInt(6);
            return ultimoResultado;
        }
        else{
            ultimoResultado=1;
            return ultimoResultado;
        }
    }
    
    Boolean salgoDeLaCarcel(){
        int a=tirar();
            return a>=5;
            
    }
    
    int quienEmpieza(int n){
         int numero;
         numero=random.nextInt(n);
         return numero;
    }
    
    public void setDebug(Boolean d){
         if(d){
             debug=d;
             Diario.getInstance().ocurreEvento("Debug on(avanzas una unidad)");
         }
         else{
             debug=d;
             Diario.getInstance().ocurreEvento("Debug off(avanzas segun el dado)");        
         }
             
    }
    
    int getUltimoResultado(){
        return ultimoResultado;
    }
    
    
}
