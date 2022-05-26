import 'Alquiler.dart';
import 'package:flutter/material.dart';

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

    if(alq.length != 0.0)
      coste_medio = coste / alq.length;

    return coste_medio;
  }

  double calcularTiempoMedio(List<Alquiler> alq) {
    double tmp = 0.0;
    double tiempo_medio = 0.0;
    for (int i = 0; i < alq.length; i++) {
      tmp += alq[i].getTiempo();
    }
    if(alq.length != 0.0)
      tiempo_medio = tmp / alq.length;

    return tiempo_medio;
  }

  void nuevoAlquiler(Alquiler alq) {
    _alquileres.add(alq);
  }

  void mostrarObjetivo(BuildContext context) {
    List<String> deporte = [];
    deporte.add('Volleyball');
    deporte.add('Baloncesto');
    deporte.add('Futbol');

    print('Tiempo y coste medio de los alquileres');
    int a = _alquileres.length;
    print('Numero total de alquileres: ${a}');
    double tmp_medio_futbol = 0.0, coste_medio_futbol = 0.0;
    double tmp_medio_volley = 0.0, coste_medio_volley = 0.0;
    double tmp_medio_basket = 0.0, coste_medio_basket = 0.0;

    for (int i = 0; i < deporte.length; i++) {
      List<Alquiler> alq = [];
      double tmp_medio = 0.0, coste_medio = 0.0;

      alq = conseguirAlquileres(deporte[i]);

      if (alq.length != 0) {
        tmp_medio = calcularTiempoMedio(alq);
        coste_medio = calcularCosteMedio(alq);
      }

      if(deporte[i] == 'Futbol'){
        tmp_medio_futbol = calcularTiempoMedio(alq);
        coste_medio_futbol = calcularCosteMedio(alq);
      }
      else if (deporte[i] == 'Baloncesto'){
        tmp_medio_basket =  calcularTiempoMedio(alq);
        coste_medio_basket = calcularCosteMedio(alq);
      }
      else if(deporte[i] == 'Volleyball'){
        tmp_medio_volley = calcularTiempoMedio(alq);
        coste_medio_volley = calcularCosteMedio(alq);
      }

      print('Los resultados para el ${deporte[i]} son:');
      print('Numero de alquileres: ${alq.length}');
      print('Tiempo medio de alquiler: ${tmp_medio} minutos');
      print('Coste medio de alquiler: ${coste_medio} euros');
    }

    showAlert(tmp_medio_futbol, coste_medio_futbol, tmp_medio_volley,
        coste_medio_volley, tmp_medio_basket, coste_medio_basket, context);
  }

  void showAlert(double tmp_medio_futbol, double coste_medio_futbol, double
                tmp_medio_volley, double coste_medio_volley, double
                tmp_medio_basket, double coste_medio_basket,
                BuildContext context) {

    showDialog(
        context: context,
        builder: (context) => AlertDialog(
          title: Text("Tiempo y coste medio de los alquileres"),
          content: Text("Futbol: Tiempo -> " + tmp_medio_futbol.toString() + ", Precio -> " + coste_medio_futbol.toStringAsFixed(2) + ".\n"
                        + "Volleyball: Tiempo -> " + tmp_medio_volley.toString() + ", Precio -> " + coste_medio_volley.toStringAsFixed(2) + ".\n"
                        + "Baloncesto: Tiempo -> " + tmp_medio_basket.toString() + ", Precio -> " + coste_medio_basket.toStringAsFixed(2) + ".\n"),
          actions: [
            RaisedButton(
              child: Text('OK'),
              onPressed: () {
                Navigator.of(context).pop();
              },
            ),
          ],
        )
    );
  }

}