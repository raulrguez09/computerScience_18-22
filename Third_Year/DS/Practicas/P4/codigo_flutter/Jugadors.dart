import 'dart:convert';
import 'package:http/http.dart' as http;

class Jugadors {
  final int id;
  final String nick;
  final String password;
  final String nombreCompleto;
  final int edad;
  final int equipos_id;

  //static String _baseAddress =
  //'jsonplaceholder.typicode.com'; // "https://clados.ugr.es/DS4";

  static String _baseAddress = 'clados.ugr.es';
  static String _applicationName = '/DS4/';

  Jugadors(this.id, this.nick, this.password, this.nombreCompleto,
      this.edad, this.equipos_id);

  String toString() {
    return "Jugadors: id-> " +
        id.toString() +
        ", nick-> " +
        nick +
        ", nombreCompleto-> " +
        nombreCompleto +
        ", edad -> " +
        edad.toString();
  }

  Map<String, dynamic> toJson() => {
        'id': id,
        'nick': nick,
        'password': password,
        'nombreCompleto': nombreCompleto,
        'edad': edad,
        'equipos_id': equipos_id
      };

  Jugadors.fromJson(Map<String, dynamic> json)
      : id = json['id'],
        nick = json['nick'],
        password = json['password'],
        nombreCompleto = json['nombreCompleto'],
        edad = json['edad'],
        equipos_id = json['equipos_id'];

  static List<Jugadors> parseJugadors(String responseBody) {
    final parsed = jsonDecode(responseBody).cast<Map<String, dynamic>>();

    return parsed.map<Jugadors>((json) => Jugadors.fromJson(json)).toList();
  }

  //////////// get //////////////////
  static Future<Jugadors> getJugadors(String id) async {

    final response = await http
        .get(Uri.https(_baseAddress, _applicationName + '/usuarios/' + id + '.json'),
      headers: <String, String>{
        'Content-Type': 'application/json; charset=UTF-8',
      },
    );

    if (response.statusCode == 200)
      return Jugadors.fromJson(jsonDecode(response.body));
    else
      throw Exception('Failed to get pito');
  }

  static Future<int> getIdEquipoJugador(String id) async {
    final response = await http
        .get(Uri.https(_baseAddress, _applicationName + '/usuarios/' + id + '.json'),
      headers: <String, String>{
        'Content-Type': 'application/json; charset=UTF-8',
      },
    );

    if (response.statusCode == 200)
      return await Jugadors.fromJson(jsonDecode(response.body)).equipos_id;
    else
      throw Exception('Failed to get pito');
  }


  static Future<List<Jugadors>> getAllJugadors() async {
    final response = await http.get(
      Uri.https(_baseAddress, _applicationName + '/usuarios.json'),
      headers: <String, String>{
        'Content-Type': 'application/json; charset=UTF-8',
      },
    );

    if (response.statusCode == 200)
      return parseJugadors(response.body);
    else
      throw Exception('Failed to get pito');
  }



  /*static signIn(String nick, String password) async {
    Map data = {'Nick': nick, 'Contraseña': password};

    final response = await http.post(
        Uri.https(_baseAddress, _applicationName + '/login'),
        headers: <String, String>{
          'Content-Type': 'application/json; charset=UTF-8'
        },
        body: jsonEncode(data));

    if (response.statusCode == 201)
      return response.body;
    else
      throw Exception('no lol');
  }*/
  ////////////// create ///////////////

  static Future<Jugadors> createJugadors(String title) async {
    final response = await http.post(
      Uri.https(_baseAddress, '/usuarios/'),
      headers: <String, String>{
        'Content-Type': 'application/json; charset=UTF-8',
      },
      body: jsonEncode(<String, String>{'edad': title}),
    );
    if (response.statusCode == 201)
      return Jugadors.fromJson(jsonDecode(response.body));
    else
      throw Exception('Failed to create Jugadors');
  }

//////////// delete //////////////////

  static Future<Jugadors> deleteJugadors(String id) async {
    final http.Response response = await http.delete(
      Uri.https(_baseAddress, '/usuarios/' + id),
      headers: <String, String>{
        'Content-Type': 'application/json; charset=UTF-8',
      },
    );
    if (response.statusCode == 200)
      return Jugadors.fromJson(jsonDecode(response.body));
    else
      throw Exception('Failed to delete Jugadors.');
  }

  /////////// update /////////

  static Future<Jugadors> updateJugadors(String title, String id) async {
    final http.Response response = await http.put(
      Uri.https(_baseAddress, '/usuarios/' + id),
      headers: <String, String>{
        'Content-Type': 'application/json; charset=UTF-8',
      },
      body: jsonEncode(<String, String>{
        'title': title,
      }),
    );
    if (response.statusCode == 200)
      return Jugadors.fromJson(jsonDecode(response.body));
    else
      throw Exception('Failed to update Jugadors');
  }
}
