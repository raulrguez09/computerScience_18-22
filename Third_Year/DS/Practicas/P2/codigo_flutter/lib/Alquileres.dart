import 'Alquiler.dart';

class Alquileres{
  List<Alquiler> alquileres = new List();

  void setNuevoAlquiler(Alquiler alq){
    alquileres.add(alq);
  }

  bool existeReserva(String ubi, String fecha){
    bool existe = false;
    for(int i = 0; i < alquileres.length; i++){
      if(alquileres[i].getUbicacion() == ubi && alquileres[i].getFecha() == fecha){
        print("papita");
        existe = true;
      }
    }
    return existe;
  }

  void muestraAlquileres(){
    for(int i = 0; i < alquileres.length; i++){
      print(alquileres[i].getUbicacion() + alquileres[i].getFecha());
    }
  }

}