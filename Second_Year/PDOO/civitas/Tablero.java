/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package civitas;

/**
 *
 * @author Raul Rodriguez Perez
 */
import java.util.ArrayList;

public class Tablero {
    private int numCasillaCarcel;
    private int porSalida;
    private Boolean tieneJuez;
    private ArrayList<Casilla> casillas=null;
     
    
    Tablero(int indice){
        if(indice>=1)
            numCasillaCarcel=indice;
        else
            numCasillaCarcel=1;
        
        casillas=new ArrayList();
        casillas.add(new Casilla("Salida"));
        porSalida=0;
        tieneJuez=false;
    }
    
    private Boolean correcto(){
        return tieneJuez && casillas.size()>numCasillaCarcel;
    }
    
    private Boolean correcto(int numCasilla){
        return correcto() && casillas.size()>numCasilla;
    }
    
    int getCarcel(){
        return numCasillaCarcel;
    }
    
    int getPorSalida(){
        if(porSalida>0){
            int a=porSalida;
            porSalida--;
             return a;
        }
        else 
            return porSalida;
    }
    
    void añadeCasilla(Casilla casilla){
        if(casillas.size()==numCasillaCarcel){
            casillas.add(new Casilla("Cárcel"));
             casillas.add(casilla);
            }
        else
             casillas.add(casilla);
    }
    
    void añadeJuez(){
        if(!tieneJuez){
            casillas.add(new Casilla(numCasillaCarcel,"Juez"));
            tieneJuez=true;
        }
    }
    
    Casilla getCasilla(int numCasilla){
        if(correcto(numCasilla))
            return casillas.get(numCasilla);
        else
            return null;
        
    }
    
    int nuevaPosicion(int actual, int tirada){
        if(correcto()){
        int a=actual+tirada;
        int b=(actual+tirada)%casillas.size();
            if(a==b)
                return a;
            else {
                porSalida++;
                return b;
            }
                }
        else
            return -1;        
    }
    
    int calcularTirada(int origen, int destino){
        int a=destino-origen;
        if(a<0){
             porSalida++;
             return a+casillas.size();
        }
        else
            return a;
    }
    
}
