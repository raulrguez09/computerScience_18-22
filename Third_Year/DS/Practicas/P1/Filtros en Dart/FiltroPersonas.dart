import 'Filtro.dart';
import 'Alquiler.dart';

class FiltroPersonas implements Filtro{
  double _descuento = 0.1;

  void ejecutar(Alquiler alq){
    String deporte = alq.getDeporte();
    int n_personas = alq.getPersonas();
    double coste = alq.getPrecio();

    if((deporte == "VolleyBall" && n_personas == 12) || (deporte == "Futbol" && n_personas == 11) || (deporte == "Baloncesto" && n_personas == 10)){
      coste = coste - (coste * _descuento);
    }
    alq.setPrecio(coste);
  }
  FiltroPersonas(){}
}