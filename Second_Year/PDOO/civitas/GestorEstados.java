package civitas;

class GestorEstados {
  EstadosJuego estadoInicial() {
    return (EstadosJuego.INICIO_TURNO);
  }
  
  OperacionesJuego operacionesPermitidas(Jugador jugador, EstadosJuego estado) {
    OperacionesJuego op = null;

    switch (estado) {
      case INICIO_TURNO :
        if (jugador.encarcelado)
          op = OperacionesJuego.SALIRCARCEL;
        else
          op = OperacionesJuego.AVANZAR;
        break;

      case DESPUES_CARCEL :
        op = OperacionesJuego.PASARTURNO;
        break;

      case DESPUES_AVANZAR :
        if (jugador.encarcelado)
          op = OperacionesJuego.PASARTURNO;
        else if (jugador.getPuedeComprar())
          op = OperacionesJuego.COMPRAR;
        else if (jugador.tieneAlgoQueGestionar())
          op = OperacionesJuego.GESTIONAR;
        else
          op = OperacionesJuego.PASARTURNO;
        break;

      case DESPUES_COMPRAR :
        if (jugador.tieneAlgoQueGestionar())
          op = OperacionesJuego.GESTIONAR;
        else
          op = OperacionesJuego.PASARTURNO;
        break;

      case DESPUES_GESTIONAR :
        if(jugador.tieneHotel())
            op = OperacionesJuego.PONER_PISCINA;
        else 
          op
                  = OperacionesJuego.PASARTURNO;
        break; 
    }
    return op;
  }
  
  EstadosJuego siguienteEstado (Jugador jugador, EstadosJuego estado, OperacionesJuego operacion) {
    EstadosJuego siguiente = null;

    switch (estado) {
      case INICIO_TURNO :
        if (operacion==OperacionesJuego.SALIRCARCEL)
          siguiente = EstadosJuego.DESPUES_CARCEL;
        else if (operacion==OperacionesJuego.AVANZAR)
          siguiente = EstadosJuego.DESPUES_AVANZAR;
        break;

      case DESPUES_CARCEL :
        if (operacion==OperacionesJuego.PASARTURNO)
          siguiente = EstadosJuego.INICIO_TURNO;
        break;

      case DESPUES_AVANZAR :
        switch (operacion) {
          case PASARTURNO :
            siguiente = EstadosJuego.INICIO_TURNO;
            break;
          case COMPRAR :
            siguiente = EstadosJuego.DESPUES_COMPRAR;
            break;
          case GESTIONAR :
            siguiente = EstadosJuego.DESPUES_GESTIONAR;
            break;
        }
        break;

      case DESPUES_COMPRAR :
        if (operacion==OperacionesJuego.GESTIONAR)
          siguiente = EstadosJuego.DESPUES_GESTIONAR;
        else if (operacion==OperacionesJuego.PASARTURNO)
          siguiente = EstadosJuego.INICIO_TURNO;
        break;
//EXAMEN
      
       
      case DESPUES_GESTIONAR:
          if(operacion ==OperacionesJuego.PASARTURNO)
              siguiente = EstadosJuego.INICIO_TURNO;
          else
              siguiente= EstadosJuego.DESPUES_PISCINA;
          break;           
                      
      case DESPUES_PISCINA :
         operacion=OperacionesJuego.PASARTURNO; 
         break; 
    }
//FIN EXAMEN
    Diario.getInstance().ocurreEvento("De: "+estado.toString()+ " con "+operacion.toString()+ " sale: "+siguiente.toString());

    return siguiente;
  }

}