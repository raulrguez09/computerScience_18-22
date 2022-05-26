import 'package:flutter_test/flutter_test.dart';
import 'package:ejemplods/FiltroIVA.dart';
import 'package:ejemplods/Alquiler.dart';

void main() {
  FiltroIVA filtro = new FiltroIVA();
  Alquiler alq = new Alquiler();
  double precio_prueba = alq.getPrecio() + alq.getPrecio() * 0.21;

  group('FiltroIVA', (){
    test('Value should start at 5.0', (){

      expect(alq.getPrecio(), 5.0);
    });

    test('Must be multiplied by 0.21', (){
      filtro.ejecutar(alq);

      expect(alq.getPrecio(), precio_prueba);
    });
  });
}