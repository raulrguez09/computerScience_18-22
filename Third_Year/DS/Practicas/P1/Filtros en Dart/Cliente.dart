import 'Alquiler.dart';
import 'dart:math';

class Cliente{
  Alquiler alquiler = new Alquiler();
  Cliente(){
    var rand = new Random();
    List<String> _deportes = ["Futbol","Baloncesto","Volleyball"];
    double precio_inicial = 5.0;
    int numero_personas = 0;
    int tiempo_alquiler = rand.nextInt(100) + 20;
    int dep = rand.nextInt(3);

    if(dep == 0)
      numero_personas = rand.nextInt(22) + 11;
    else if(dep == 1)
      numero_personas = rand.nextInt(10) + 5;
    else if(dep == 2)
      numero_personas = rand.nextInt(12) + 6;

    alquiler.setAlquiler(precio_inicial, _deportes[dep], tiempo_alquiler, numero_personas);
  }

  Alquiler getAlquiler(){
    return alquiler;
  }

  void setAlquiler(Alquiler alq){
    alquiler.setAlquiler(alq.getPrecio(), alq.getDeporte(), alq.getTiempo(), alq.getPersonas());
  }
}