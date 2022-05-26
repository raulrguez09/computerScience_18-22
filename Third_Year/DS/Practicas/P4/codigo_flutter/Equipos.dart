import 'dart:convert';
import 'package:http/http.dart' as http;
import 'package:ejemplods/Jugadors.dart';
class Equipos {
  final int id;
  final String Siglas;
  final String Deporte;
  final String Nombreequipo;

  //static String _baseAddress =
  //'jsonplaceholder.typicode.com'; // "https://clados.ugr.es/DS4";

  static String _baseAddress = 'clados.ugr.es';
  static String _applicationName = '/DS4/';

  Equipos(this.id,this.Deporte, this.Siglas, this.Nombreequipo);

  String toString() {
    return "Equipo: id-> " +
        this.id.toString() +
        ", Deporte-> " +
        this.Deporte +
        ", Siglas-> " +
        this.Siglas +
        ", Nombreequipo -> " +
        this.Nombreequipo;
  }

  Map<String, dynamic> toJson() => {
    'id': id,
    'deporte': Deporte,
    'siglas': Siglas,
    'nombreEquipo': Nombreequipo
  };

  Equipos.fromJson(Map<String, dynamic> json)
      : id = json['id'],
        Deporte = json['deporte'],
        Siglas = json['diglas'],
        Nombreequipo = json['nombreEquipo'];

  static List<Equipos> parseEquipos(String responseBody) {
    final parsed = jsonDecode(responseBody).cast<Map<String, dynamic>>();

    return parsed.map<Equipos>((json) => Equipos.fromJson(json)).toList();
  }

  //////////// get //////////////////
  static Future<Equipos> getEquipos(String id) async {
    final response = await http
        .get(Uri.https(_baseAddress, _applicationName + '/equipos/' + id + '.json'),
      headers: <String, String>{
        'Content-Type': 'application/json; charset=UTF-8',
      },
    );

    if (response.statusCode == 200)
      return Equipos.fromJson(jsonDecode(response.body));
    else
      throw Exception('Failed to get pito');
  }


  static Future<List<Equipos>> getAllEquipos() async {
    final response = await http.get(
      Uri.https(_baseAddress, _applicationName + '/equipos.json'),
      headers: <String, String>{
        'Content-Type': 'application/json; charset=UTF-8',
      },
    );

    if (response.statusCode == 200)
      return parseEquipos(response.body);
    else
      throw Exception('Failed to get pito');
  }


  static Future<List<Jugadors>> getMiembrosEquipo(String idEquipo) async {
    List<Jugadors> jugadores= await Jugadors.getAllJugadors();
    print(jugadores.first.nick);
    List<Jugadors> res;

    var it = jugadores.iterator;
    while (it.moveNext()) {
      if(it.current.equipos_id.toString() == idEquipo)
        res.add(it.current);
    }
    print(res.first.nick+"89");

    return res;
  }


  static Future<List<Jugadors>> getMiembrosEquipoPorIdJugador(String idJugador) async {
    final response = await http
        .get(Uri.https(_baseAddress, _applicationName + '/usuarios/' + idJugador + '.json'),
      headers: <String, String>{
        'Content-Type': 'application/json; charset=UTF-8',
      },
    );

    int idEquipo;

    if (response.statusCode == 200)
      idEquipo= Jugadors.fromJson(jsonDecode(response.body)).equipos_id;
    else
      throw Exception('Failed to get Jugador');


    List<Jugadors> jugadores= await Jugadors.getAllJugadors();
    List<Jugadors> res= [];

    for(int i=0; i< jugadores.length; i++)
      if(jugadores[i].equipos_id == idEquipo)
        res.add(jugadores[i]);

      return res;
  }


  static Future<Equipos> getEquipoJugador(String idJugador) async {
    final response = await http
        .get(Uri.https(_baseAddress, _applicationName + '/usuarios/' + idJugador + '.json'),
      headers: <String, String>{
        'Content-Type': 'application/json; charset=UTF-8',
      },
    );
    if (response.statusCode == 200)
      return await getEquipos(Jugadors.fromJson(jsonDecode(response.body)).equipos_id.toString());
    else
      throw Exception('Failed to get equipo');
  }


////////////// create ///////////////

  /*static Future<Equipos> createEquipos(String title) async {
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
  }*/
}
