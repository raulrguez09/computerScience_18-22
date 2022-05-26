import 'Filtro.dart';
import 'Alquiler.dart';

class FiltroTiempo implements Filtro{

  void ejecutar(Alquiler alq){
    int minutos = alq.getTiempo();
    double coste = alq.getPrecio();

    if(minutos <= 30)
      coste += 3.5;
    else if(minutos <= 50 && minutos > 30)
      coste += 4.0;
    else if(minutos <= 70 && minutos > 50)
      coste += 4.5;
    else if(minutos <= 90 && minutos > 70)
      coste += 5.0;
    else if(minutos <= 120 && minutos > 90)
      coste += 6.0;

    alq.setPrecio(coste);
  }

  FiltroTiempo(){}

}