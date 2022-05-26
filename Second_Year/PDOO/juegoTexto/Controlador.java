/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package juegoTexto;


import civitas.CivitasJuego;
import civitas.Diario;
import civitas.OperacionesJuego;
import civitas.SalidasCarcel;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Scanner;
import civitas.Casilla;
import civitas.GestionesInmobiliarias;
import civitas.Jugador;
import civitas.OperacionInmobiliaria;
import civitas.TituloPropiedad;
import civitas.Respuestas;
/**
 *
 * @author Raul Rodriguez Perez
 */
public class Controlador {
    private CivitasJuego juego;
    private VistaTextual vista;
    
    
    
    public Controlador(CivitasJuego juego,VistaTextual vista){
        this.juego=juego;
        this.vista=vista;
    }
    
    public void juega(){
        vista.setCivitasJuego(juego);
        while(!juego.finalDelJuego()){
            vista.actualizarVista();
            vista.pausa();
            OperacionesJuego op=juego.siguientePaso();
            if(op!=civitas.OperacionesJuego.PASARTURNO)
                vista.mostrarEventos();
            
            if(!juego.finalDelJuego()){
                switch(op){
                    case COMPRAR:
                        Respuestas res=vista.comprar();
                        if(res==Respuestas.SI)
                            juego.comprar();
                            juego.siguientePasoCompletado(op);
                        
                        break;
                    case GESTIONAR:
                        vista.gestionar();
                        vista.getGestion();
                        vista.getPropiedad();
                        OperacionInmobiliaria oi=new OperacionInmobiliaria(GestionesInmobiliarias.values()[vista.getGestion()],vista.getPropiedad());
                        
                        switch(GestionesInmobiliarias.values()[vista.getGestion()]){
                            case VENDER:
                                if(juego.getJugadorActual().getNombrePropiedades()!=null)
                                juego.vender(oi.getNumPropiedad());
                                break;
                            case HIPOTECAR:
                                if(juego.getJugadorActual().getNombrePropiedades()!=null)
                                juego.hipotecar(oi.getNumPropiedad());
                                break;
                            case  CANCELAR_HIPOTECA:
                                if(juego.getJugadorActual().getNombrePropiedades()!=null)
                                juego.cancelarHipoteca(oi.getNumPropiedad());
                                break;
                            case CONSTRUIR_CASA:
                                juego.construirCasa(oi.getNumPropiedad());
                                break;
                            case CONSTRUIR_HOTEL:
                                juego.construirHotel(oi.getNumPropiedad());
                                break;
                            default:
                                juego.siguientePasoCompletado(op);
                                break;
                                    
                        }
                        break;
                    
                    case SALIRCARCEL:
                        SalidasCarcel salida=vista.salirCarcel();
                        switch(salida){
                            case PAGANDO:
                                juego.salirCarcelPagando();
                                break;
                            case TIRANDO:
                                juego.salirCarcelTirando();
                                break;
           
                            }
                            juego.siguientePasoCompletado(op);
                        break;
                        
                    case PONER_PISCINA:
                        vista.ponerPiscina();
                        int i = vista.getPropiedad();
                        juego.ponerPiscina(i);
                        juego.siguientePasoCompletado(op);
                        
                        
                }
                
                
            }
            else{
               ArrayList<Jugador>lista=juego.ranking();
               for(int i=0;i<lista.size();i++)
                  System.out.println(lista.get(i).getNombre()+"\n");
            }
                
        }
        
        
    }
}
