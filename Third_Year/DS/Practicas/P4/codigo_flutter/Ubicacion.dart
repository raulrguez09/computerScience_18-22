
class Ubicacion{
  List<String> ubicaciones;
  
  Ubicacion(){
    ubicaciones.add("PISTA 1");
    ubicaciones.add("PISTA 2");
    ubicaciones.add("PISTA 3");
    ubicaciones.add("PISTA 4");
    ubicaciones.add("PISTA 5");
    ubicaciones.add("PISTA 6");
    ubicaciones.add("PISTA 7");
    ubicaciones.add("PISTA 8");
    ubicaciones.add("PISTA 9");
    ubicaciones.add("PISTA 10");
  }

  String getUbicacion(int i){
    return ubicaciones[i];
  }

  void setUbicacion(String ub){
    ubicaciones.add(ub);
  }

  bool existeUbicacion(String ub){
    bool existe = false;
    for(int i = 0; i < ubicaciones.length; i++){
      if(ubicaciones[i] == ub){
        existe = true;
      }
    }
    return existe;
  }


}