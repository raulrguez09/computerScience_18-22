import 'Filtro.dart';
import 'Alquiler.dart';

class CadenaFiltro{
  List<Filtro> _filtros = [];

  void addFiltro(Filtro f){

    _filtros.add(f);
  }

  void ejecutar(Alquiler alq){
    for(var i = 0; i < _filtros.length ;i++){
      _filtros[i].ejecutar(alq);
    }
  }
}