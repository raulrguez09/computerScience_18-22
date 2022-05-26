import 'Filtro.dart';
import 'Alquiler.dart';

class FiltroIVA implements Filtro {
  double IVA = 0.21;
  void ejecutar(Alquiler alq) {
    double precio = alq.getPrecio();
    precio = precio + precio * IVA;
    alq.setPrecio(precio);
  }
  FiltroIva(){}
}
