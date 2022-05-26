import 'package:flutter_test/flutter_test.dart';
import 'package:ejemplods/Objetivo.dart';
import 'package:ejemplods/Alquiler.dart';

void main() {
  Objetivo obj = new Objetivo();
  Alquiler alq1 = new Alquiler();
  Alquiler alq2 = new Alquiler();
  Alquiler alq3 = new Alquiler();
  List<Alquiler> alquileres = [];

  alq1.setAlquiler(10.0, 'Futbol', 45, 11, 'Maracena', '02/02/2020');
  alq2.setAlquiler(13.2, 'Baloncesto', 60, 11, 'Maracene', '04/02/2020');
  alq3.setAlquiler(6.5, 'Futbol', 110, 11, 'Maraceno', '03/02/2020');

  alquileres.add(alq1);
  alquileres.add(alq2);
  alquileres.add(alq3);

  double coste_medio = (10 + 13.2 + 6.5) / 3.0;
  double tmp_medio = (45 + 60 + 110) / 3.0;

  group('FiltroIVA', (){
    test('Average cost should be the sum of the costs between the number of rentals', (){
      double coste = obj.calcularCosteMedio(alquileres);

      expect(coste, coste_medio);
    });

    test('Average time should be the sum of the times between the number of rentals', (){
      double tmp = obj.calcularTiempoMedio(alquileres);

      expect(tmp, tmp_medio);
    });
  });
}