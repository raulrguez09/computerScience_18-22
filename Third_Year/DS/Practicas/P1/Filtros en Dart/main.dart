
import 'GestorFiltros.dart';
import 'Objetivo.dart';
import 'Cliente.dart';

void main() {
  print('hola');
  GestorFiltros gestor = new GestorFiltros();
  Objetivo target = new Objetivo();

  for(int i = 0; i < 10 ; i++){
    Cliente client = new Cliente();
    gestor.filtrar(client.getAlquiler());
    target.nuevoAlquiler(client.getAlquiler());
    if(i%5 == 0){
      target.mostrarObjetivo();
    }
  }
}
