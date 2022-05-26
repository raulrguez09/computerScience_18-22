import 'dart:convert';
import 'package:http/http.dart' as http;

class Encuentros {
  final int id;
  final String deporte;
  final String fecha;
  final int tiempo;
  final int numperson;
  final String metodopago;
  final String ubicacion;
  final int precio;
  final int usuario_id;


  //static String _baseAddress =
  //'jsonplaceholder.typicode.com'; // "https://clados.ugr.es/DS4";

  static String _baseAddress = 'clados.ugr.es';
  static String _applicationName = '/DS4/';

  Encuentros(this.id, this.deporte, this.fecha, this.tiempo, this.numperson,
    this.metodopago, this.ubicacion, this.precio, this.usuario_id);

  String toString() {
    return "Encuentros: id-> " +
        id.toString() +
        ", deporte-> " +
        deporte +
        ", precio-> " +
        precio.toString();
  }

  Map<String, dynamic> toJson() => {
    'id': id,
    'deporte': deporte,
    'fecha': fecha,
    'tiempo': tiempo,
    'numperson': numperson,
    'metodopago': metodopago,
    'ubicacion': ubicacion,
    'precio': precio,
    'usuario_id': usuario_id
  };

  Encuentros.fromJson(Map<String, dynamic> json)
      : id = json['id'],
        deporte = json['deporte'],
        fecha = json['fecha'],
        tiempo = json['tiempo'],
        numperson = json['numperson'],
        metodopago = json['metodopago'],
        ubicacion = json['ubicacion'],
        precio = json['precio'],
        usuario_id = json['usuario_id'];

  static List<Encuentros> parseEncuentros(String responseBody) {
    final parsed = jsonDecode(responseBody).cast<Map<String, dynamic>>();

    return parsed.map<Encuentros>((json) => Encuentros.fromJson(json)).toList();
  }

  //////////// get //////////////////
  static Future<Encuentros> getEncuentro(String id) async {
    final response = await http
        .get(Uri.https(_baseAddress, _applicationName + '/encuentros/' + id),
      headers: <String, String>{
        'Content-Type': 'application/json; charset=UTF-8',
      },
    );

    if (response.statusCode == 200)
      return Encuentros.fromJson(jsonDecode(response.body));
    else
      throw Exception('Failed to get encuentro');
  }

  static Future<List<Encuentros>> getAllEncuentros() async {
    final response = await http.get(
      Uri.https(_baseAddress, _applicationName + '/encuentros.json'),
      headers: <String, String>{
        'Content-Type': 'application/json; charset=UTF-8',
      },
    );

    if (response.statusCode == 200)
      return parseEncuentros(response.body);
    else
      throw Exception('Failed to get encuentros');
  }

  ////////////// create ///////////////

  static Future<Encuentros> createEncuentro(String deporte, String fecha,
      int tiempo, int numperson, String metodopago, String ubicacion, int
    precio, int usuario_id) async {
    final response = await http.post(
      Uri.https(_baseAddress, _applicationName + 'api/v1/encuentros'),
      headers: <String, String>{
        'Content-Type': 'application/json; charset=UTF-8',
      },
      body: jsonEncode(<String, Object>{
        'deporte': deporte,
        'fecha': fecha,
        'tiempo': tiempo,
        'numperson': numperson,
        'metodopago': metodopago,
        'ubicacion': ubicacion,
        'precio': precio,
        'usuario_id': usuario_id}),
    );
    if (response.statusCode == 201)
      return Encuentros.fromJson(jsonDecode(response.body));
    else
      throw Exception('Failed to create encuentro' + response.statusCode.toString());
  }

//////////// delete //////////////////

  static Future<Encuentros> deleteEncuentros(String id) async {
    final http.Response response = await http.delete(
      Uri.https(_baseAddress, '/encuentros/' + id),
      headers: <String, String>{
        'Content-Type': 'application/json; charset=UTF-8',
      },
    );
    if (response.statusCode == 200)
      return Encuentros.fromJson(jsonDecode(response.body));
    else
      throw Exception('Failed to delete Encuentros.');
  }

  /////////// update /////////

  static Future<Encuentros> updateEncuentros(String title, String id) async {
    final http.Response response = await http.put(
      Uri.https(_baseAddress, '/encuentros/' + id),
      headers: <String, String>{
        'Content-Type': 'application/json; charset=UTF-8',
      },
      body: jsonEncode(<String, String>{
        'title': title,
      }),
    );
    if (response.statusCode == 200)
      return Encuentros.fromJson(jsonDecode(response.body));
    else
      throw Exception('Failed to update Encuentros');
  }
}
