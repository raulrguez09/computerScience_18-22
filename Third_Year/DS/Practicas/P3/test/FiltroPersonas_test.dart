import 'package:flutter_test/flutter_test.dart';
import 'package:ejemplods/Alquiler.dart';
import 'package:ejemplods/FiltroPersonas.dart';

void main() {
  FiltroPersonas filtro = new FiltroPersonas();
  Alquiler alq = new Alquiler();
  double descuento_prueba = alq.getPrecio() - (alq.getPrecio() * 0.1);

  group('FiltroPersonas', (){
    test('Value should start at 0.0', (){

      expect(alq.getPersonas(), 0.0);
    });

    test('If n_personas = 10, 11 or 12; discount must be applied', (){
      alq.setPersonas(10);
      alq.setDeporte('Baloncesto');
      filtro.ejecutar(alq);

      expect(descuento_prueba, alq.getPrecio());
    });
  });
}