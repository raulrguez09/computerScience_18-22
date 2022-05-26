/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package civitas;

import java.util.ArrayList;

import java.util.Collections;
/**
 *
 * @author Raul Rodriguez Perez
 */

public class MazoSorpresas {
    
    private ArrayList<Sorpresa>sorpresas;
    private Boolean barajada;
    private int usadas;
    private Boolean debug;
    private ArrayList<Sorpresa>cartasEspeciales;
    private Sorpresa ultimaSorpresa;
    
    
    void init(){
        sorpresas=new ArrayList();
        cartasEspeciales=new ArrayList();
        barajada=false;
        usadas=0;
    }
    
    MazoSorpresas(Boolean d){
        debug=d;
        init();
        if(d)
            Diario.getInstance().ocurreEvento("Debug ON(mazo no se baraja)");   
    }
    
    MazoSorpresas(){
        init();
        debug=false;   
    }
    
    
    void alMazo(Sorpresa s){
        if(!barajada)
            sorpresas.add(s);
            
    }
    
    Sorpresa siguiente(){
        if((!barajada||usadas==sorpresas.size())&& !debug){
            Collections.shuffle(sorpresas);
            usadas=0;
            barajada=true;
        }
         usadas++;
         Sorpresa a=sorpresas.get(0);
         sorpresas.remove(0);
         sorpresas.add(a);
         ultimaSorpresa=a;
         return ultimaSorpresa;
    }
    
    
    void inhabilitarCartaEspecial(Sorpresa sorpresa){
       for(int i=0; i<sorpresas.size(); i++){
           if(sorpresas.get(i)==sorpresa ){
               sorpresas.remove(i);
               cartasEspeciales.add(sorpresa);
               Diario.getInstance().ocurreEvento("Se ha inhabilitado una carta del mazo sorpresas y se ha añadido al de cartas especiales");
           }       
       }      
    }
    
    
    void habilitarCartaEspecial(Sorpresa sorpresa){
         for(int i=0; i< cartasEspeciales.size(); i++){
           if( cartasEspeciales.get(i)==sorpresa ){
               sorpresas.remove(i);
               sorpresas.add(sorpresa);
               Diario.getInstance().ocurreEvento("Se ha habilitado una carta al mazo sorpresas proveniente de las cartas especiales");
           }       
       }      
    }

    void habilitarCartaEspecial(TipoSorpresa tipo) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }
    
    
}
