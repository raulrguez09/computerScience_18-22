import 'dart:convert';
import 'package:http/http.dart' as http;

class Apuntados {
  final int id;
  final int usuarios_id;
  final int encuentros_id;


  //static String _baseAddress =
  //'jsonplaceholder.typicode.com'; // "https://clados.ugr.es/DS4";

  static String _baseAddress = 'clados.ugr.es';
  static String _applicationName = '/DS4/';

  Apuntados(this.id, this.usuarios_id, this.encuentros_id);

  String toString() {
    return "Apuntados: id-> " +
        id.toString() +
        ", usuarios_id-> " +
        usuarios_id.toString() +
        ", encuentros_id -> " +
        encuentros_id.toString();
  }

  Map<String, dynamic> toJson() => {
    'id': id,
    'usuarios_id': usuarios_id,
    'encuentros_id': encuentros_id
  };

  Apuntados.fromJson(Map<String, dynamic> json)
      : id = json['id'],
        usuarios_id = json['usuarios_id'],
        encuentros_id = json['encuentros_id'];

  static List<Apuntados> parseApuntados(String responseBody) {
    final parsed = jsonDecode(responseBody).cast<Map<String, dynamic>>();

    return parsed.map<Apuntados>((json) => Apuntados.fromJson(json)).toList();
  }

  //////////// get //////////////////
  static Future<Apuntados> getApuntado(String id) async {
    final response = await http
        .get(Uri.https(_baseAddress, _applicationName + '/apuntados/' + id + '.json'),
      headers: <String, String>{
        'Content-Type': 'application/json; charset=UTF-8',
      },
    );

    if (response.statusCode == 200)
      return Apuntados.fromJson(jsonDecode(response.body));
    else
      throw Exception('Failed to get apuntado');
  }

  static Future<List<Apuntados>> getAllApuntados() async {
    final response = await http.get(
      Uri.https(_baseAddress, _applicationName + '/apuntados.json'),
      headers: <String, String>{
        'Content-Type': 'application/json; charset=UTF-8',
      },
    );

    if (response.statusCode == 200)
      return parseApuntados(response.body);
    else
      throw Exception('Failed to get Apuntados');
  }

  ////////////// create ///////////////

  static Future<Apuntados> createApuntado(int usuarios_id,int encuentros_id) async {
    final response = await http.post(
      Uri.https(_baseAddress, _applicationName + 'api/v1/apuntados'),
      headers: <String, String>{
        'Content-Type': 'application/json; charset=UTF-8',
        "Access-Control_Allow_Origin": "*"
      },
      body: jsonEncode(<String, int>{
        'usuarios_id': usuarios_id,
        'encuentros_id': encuentros_id}),
    );
    if (response.statusCode == 201)
      return Apuntados.fromJson(jsonDecode(response.body));
    else
      throw Exception('Failed to create apuntados ' + response.statusCode.toString());
  }

//////////// delete //////////////////

  static Future<Apuntados> deleteApuntados(String id) async {
    final http.Response response = await http.delete(
      Uri.https(_baseAddress, 'api/v1/apuntados/' + id),
      headers: <String, String>{
        'Content-Type': 'application/json; charset=UTF-8',
      },
    );
    if (response.statusCode == 200)
      return Apuntados.fromJson(jsonDecode(response.body));
    else
      throw Exception('Failed to delete apuntados.');
  }

}