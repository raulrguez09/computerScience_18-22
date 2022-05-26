class Alquiler{
  double _precio;
  int _tiempo, _n_personas;
  String _deporte;

  double getPrecio(){
    return _precio;
  }

  String getDeporte(){
    return _deporte;
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

  void setAlquiler(double coste, String dep, int tmp, int n){
    _precio = coste;
    _deporte = dep;
    _tiempo = tmp;
    _n_personas = n;
  }
}