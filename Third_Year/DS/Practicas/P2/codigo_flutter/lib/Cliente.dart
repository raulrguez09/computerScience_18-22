import 'Alquiler.dart';
import 'dart:math';
import 'Ubicacion.dart';

class Cliente{
  Alquiler alquiler = new Alquiler();
  Cliente(){}

  Alquiler getAlquiler(){
    return alquiler;
  }

  void setAlquiler(Alquiler alq){
    alquiler.setAlquiler(alq.getPrecio(), alq.getDeporte(), alq.getTiempo(), alq.getPersonas(),alq.getUbicacion(),alq.getFecha());
  }
}