import 'Ubicacion.dart';

class Alquiler{
  double _precio;
  int _tiempo, _n_personas;
  String _deporte, _fecha, _ubicacion;

  Alquiler(){
    _precio = 5.0;
    _tiempo = _n_personas = 0;
    _deporte = _fecha = _ubicacion = '';
  }

  double getPrecio(){
    return _precio;
  }

  String getDeporte(){
    return _deporte;
  }

  String getFecha(){
    return _fecha;
  }

  String getUbicacion(){
    return _ubicacion;
  }

  int getTiempo(){
    return _tiempo;
  }

  int getPersonas(){
    return _n_personas;
  }

  void setPrecio(double coste){
    _precio = coste;
  }

  void setDeporte(String dep){
    _deporte = dep;
  }

  void setTiempo(int tmp){
    _tiempo = tmp;
  }

  void setPersonas(int n){
    _n_personas = n;
  }

  void setFecha(String fech){
    _fecha = fech;
  }

  void setUbicacion(Ubicacion ub, int i){
    _ubicacion = ub.getUbicacion(i);
  }

  void setAlquiler(double coste, String dep, int tmp, int n, String ubi, String fech){
    _precio = coste;
    _deporte = dep;
    _tiempo = tmp;
    _n_personas = n;
    _ubicacion = ubi;
    _fecha = fech;
  }
}