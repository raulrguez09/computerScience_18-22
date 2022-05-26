import 'FiltroIVA.dart';
import 'FiltroPersonas.dart';
import 'FiltroTiempo.dart';
import 'Alquiler.dart';
import 'CadenaFiltro.dart';
import 'Filtro.dart';

class GestorFiltros {
  CadenaFiltro _cadenaFiltros = new CadenaFiltro();

  GestorFiltros() {
    FiltroTiempo f1 = new FiltroTiempo();
    FiltroPersonas f2 = new FiltroPersonas();
    FiltroIVA f3 = new FiltroIVA();

    _cadenaFiltros.addFiltro(f1);
    _cadenaFiltros.addFiltro(f2);
    _cadenaFiltros.addFiltro(f3);
  }

  void filtrar(Alquiler alq) {
    _cadenaFiltros.ejecutar(alq);
  }

  void setFiltro(Filtro f) {
    _cadenaFiltros.addFiltro(f);
  }
}
