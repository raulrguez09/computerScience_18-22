import 'Alquiler.dart';

class Objetivo {
  List<Alquiler> _alquileres = [];

  List<Alquiler> conseguirAlquileres(String deporte) {
    List<Alquiler> alq = [];
    for (int i = 0; i < _alquileres.length; i++) {
      if (_alquileres[i].getDeporte() == deporte) {
        alq.add(_alquileres[i]);
      }
    }

    return alq;
  }

  double calcularCosteMedio(List<Alquiler> alq) {
    double coste = 0.0;
    double coste_medio = 0.0;
    for (int i = 0; i < alq.length; i++) {
      coste += alq[i].getPrecio();
    }
    coste_medio = coste / alq.length;

    return coste_medio;
  }

  double calcularTiempoMedio(List<Alquiler> alq) {
    double tmp = 0.0;
    double tiempo_medio = 0.0;
    for (int i = 0; i < alq.length; i++) {
      tmp += alq[i].getTiempo();
    }
    tiempo_medio = tmp / alq.length;

    return tiempo_medio;
  }

  void nuevoAlquiler(Alquiler alq) {
    _alquileres.add(alq);
  }

  void mostrarObjetivo() {
    List<String> deporte = [];
    deporte.add('Volleyball');
    deporte.add('Baloncesto');
    deporte.add('Futbol');

    print('Tiempo y coste medio de los alquileres');
    int a = _alquileres.length;
    print('Numero total de alquileres: ${a}');


    for (int i = 0; i < deporte.length; i++) {
      List<Alquiler> alq = [];
      double tmp_medio = 0.0, coste_medio = 0.0;
      alq = conseguirAlquileres(deporte[i]);

      if (alq.length != 0) {
        tmp_medio = calcularTiempoMedio(alq);
        coste_medio = calcularCosteMedio(alq);
      }

      print('Los resultados para el ${deporte[i]} son:');
      print('Numero de alquileres: ${alq.length}');
      print('Tiempo medio de alquiler: ${tmp_medio} minutos');
      print('Coste medio de alquiler: ${coste_medio} euros');
    }
  }

}