import 'dart:io';
import 'package:ejemplods/Apuntados.dart';
import 'package:flutter/material.dart';
import 'Cliente.dart';
import 'Alquiler.dart';
import 'Alquileres.dart';
import 'GestorFiltros.dart';
import 'Objetivo.dart';
import 'EstrategiaPago.dart';
import 'PagoPaypal.dart';
import 'PagoTarjeta.dart';
import 'PagoTransferencia.dart';
import 'Jugadors.dart';
import 'Encuentros.dart';
import 'Apuntados.dart';
import 'Equipos.dart';


class MyHttpOverrides extends HttpOverrides {
  @override
  HttpClient createHttpClient(SecurityContext context){
    return super.createHttpClient(context)
        ..badCertificateCallback =
          (X509Certificate cert, String host, int port) => true;
  }
}

void main() {
  HttpOverrides.global = new MyHttpOverrides();
  runApp(MyApp());
}

class MyApp extends StatelessWidget {
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Práctica 2: DS',
      theme: ThemeData(
        primarySwatch: Colors.blue,
      ),

      // Modificamos el constructor pasandole el objeto
      home: LoginDemo(),
    );
  }
}

class LoginDemo extends StatefulWidget {
  @override
  _LoginDemoState createState() => _LoginDemoState();
}

class _LoginDemoState extends State<LoginDemo> {
  // Creamos la instancia del objeto
  Objetivo target = new Objetivo();
  Alquileres alquileres = new Alquileres();
  PagoPaypal paypal = new PagoPaypal();
  PagoTarjeta tarjeta = new PagoTarjeta();
  PagoTransferencia trans = new PagoTransferencia();
  Future<List<Jugadors>> _futureList;
  Map<String, String> nickJugadores = new Map<String, String>();
  Map<String, int> idJugadores = new Map<String, int>();
  int idUserLogin = -1;
  TextEditingController _controller1 = TextEditingController();
  TextEditingController _controller2 = TextEditingController();

  void initState() {
    super.initState();
    _futureList = Jugadors.getAllJugadors();
  }


  @override
  Widget build(BuildContext context) {
    return Scaffold(
      backgroundColor: Colors.white,
      appBar: AppBar(
        title: Text("Login Page"),
      ),
      body: SingleChildScrollView(
        child: Column(
          children: <Widget>[
        FutureBuilder<List<Jugadors>>(
          future: _futureList,
          builder: (context, snapshot) {
            // If the connection is done,
            // check for response data or an error.
            if (snapshot.connectionState == ConnectionState.done) {
              if (snapshot.hasData) {
                for(int i = 0; i < snapshot.data.length; i++){
                  nickJugadores.addAll({snapshot.data[i].nick: snapshot.data[i].password});
                  idJugadores.addAll({snapshot.data[i].nick: snapshot.data[i].id});
                }
              } else if (snapshot.hasError) {
                return Text("${snapshot.error}");
              }
            }
            // By default, show a loading spinner.
            return Text("");
          },
        ),
            Padding(
              padding: const EdgeInsets.only(top: 50.0),
              child: Center(
                child: Container(
                    child: Image.network(
                        'https://www.podoactiva.com/sites/default/files/sport-moments-banner.jpg')),
              ),
            ),
            Padding(
              //padding: const EdgeInsets.only(left:15.0,right: 15.0,top:0,bottom: 0),
              padding: EdgeInsets.symmetric(horizontal: 15),
              child: TextField(
                controller: _controller1,
                decoration: InputDecoration(
                    border: OutlineInputBorder(),
                    labelText: 'Username',
                    hintText: 'Enter valid username'),
              ),
            ),
            Padding(
              padding: const EdgeInsets.only(
                  left: 15.0, right: 15.0, top: 15, bottom: 20),
              //padding: EdgeInsets.symmetric(horizontal: 15),
              child: TextField(
                controller: _controller2,
                obscureText: true,
                decoration: InputDecoration(
                    border: OutlineInputBorder(),
                    labelText: 'Password',
                    hintText: 'Enter secure password'),
              ),
            ),
            Container(
              height: 50,
              width: 250,
              decoration: BoxDecoration(
                  color: Colors.blue, borderRadius: BorderRadius.circular(20)),
              child: FlatButton(
                onPressed: () {
                    var pasw_usuario = nickJugadores[_controller1.text];
                    idUserLogin = idJugadores[_controller1.text];
                    if(pasw_usuario != null && pasw_usuario == _controller2.text){
                    Navigator.push(
                        context,
                        MaterialPageRoute(
                            builder: (_) => HomePage(idUserLogin,target,
                                alquileres, paypal, tarjeta, trans,
                              title: 'Meet & Match'))
                    );
                    }
                    else{
                      loginError(context);
                    }
                  },
                child: Text(
                  'Login',
                  style: TextStyle(color: Colors.white, fontSize: 25),
                ),
              ),
            ),
          ],
        ),
      ),
    );
  }
}

class HomePage extends StatelessWidget {
  // Instanciamos el objeto y lo pasamos al constructor
  Objetivo target;
  Alquileres alquileres;
  PagoPaypal paypal;
  PagoTarjeta tarjeta;
  PagoTransferencia trans;
  int idUserLogin;
  Future<List<Encuentros>> _futureList = Encuentros.getAllEncuentros();
  List<Encuentros> encuentros = [];

  HomePage(this.idUserLogin, this.target, this.alquileres, this.paypal, this.tarjeta, this.trans,
      {Key key, this.title})
      : super(key: key);
  final String title;

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text('Meet & Match'),
          actions: <Widget>[
            Padding(
              padding: EdgeInsets.only(right: 20.0),
              child: GestureDetector(
                onTap: () {
                  Navigator.push(
                    context,
                    MaterialPageRoute(
                        builder: (context) =>  ProfilePage(idUserLogin,
                            encuentros, title: 'Meet & Match')),
                  );
                },
                child: Icon(
                  Icons.account_circle,
                  size: 26.0,
                ),
              )
            ),
          ],
      ),
      body: Center(
        child: Column(
          mainAxisAlignment: MainAxisAlignment.center,
          children: <Widget>[
            Container(
              margin: const EdgeInsets.only(left: 20.0, right: 20.0),
              padding: const EdgeInsets.only(bottom: 20.0),
              child: RichText(
                textAlign: TextAlign.center,
                text: TextSpan(
                  text: '¿Cansado de ',
                  style:  TextStyle(fontSize: 30.0, color: Colors.black),
                  children: const <TextSpan>[
                    TextSpan(text: 'no encontrar', style: TextStyle(fontWeight: FontWeight.bold)),
                    TextSpan(text: ' gente con la que practicar tu deporte '
                        'favorito?'),
                    TextSpan(text: '\n\nPues ese sufrimiento a terminado gracias a '
                    , style: TextStyle(fontSize: 20.0)),
                    TextSpan(text: ' Meet & Match.', style: TextStyle(fontSize: 20.0, fontWeight: FontWeight.bold)),
                    TextSpan(text: ' Crea tu propio equipo, tu propio encuentro, '
                        'o busca uno al que apuntarte. Miles de usuarios ya están '
                        'disfrutando de sus deportes favoritos gracias a nuestros '
                        'servicios.', style: TextStyle(fontSize: 20.0)),
                  ],
                ),
              ),
            ),
            Image.network(
                'https://media.discordapp.net/attachments/813457307374452736/847415611700543498/saber-competir-para-deportistas-min.png'),
            Container(
              child: FutureBuilder<List<Encuentros>>(
              future: _futureList,
              builder: (context, snapshot) {
              // If the connection is done,
              // check for response data or an error.
                if (snapshot.connectionState == ConnectionState.done) {
                  if (snapshot.hasData) {
                    for(int i = 0; i < snapshot.data.length; i++){
                      encuentros.addAll({snapshot.data[i]});
                    }
                  } else if (snapshot.hasError) {
                    return Text("${snapshot.error}");
                  }
                }
                // By default, show a loading spinner.
                return Text("");
              },
              ),
            ),
            Container(
              padding: const EdgeInsets.only(top: 20.0),
              child: Row(
                mainAxisAlignment: MainAxisAlignment.spaceEvenly,
                children: <Widget>[
                  new RaisedButton(
                    child: Text('Alquilar encuentro'),
                    onPressed: () {
                      Navigator.push(
                        context,
                        MaterialPageRoute(
                            builder: (context) => MySecondPage(
                                this.idUserLogin,
                                this.target,
                                this.alquileres,
                                this.paypal,
                                this.tarjeta,
                                this.trans)),
                      );
                    },
                  ),
                  new RaisedButton(
                    child: Text('Apuntarse a encuentro'),
                    onPressed: () {
                      Navigator.push(
                        context,
                        MaterialPageRoute(
                            builder: (context) =>
                                ApuntarseEncuentro(idUserLogin, encuentros)),
                      );
                    },
                  ),
                ],
              ),
            ),
          ],
        ),
      ),
    );
  }
}


class ProfileData {
  List<Jugadors> miembrosEquipoData;
  Jugadors jugadorData;
  Equipos equipoData;

  ProfileData({
    this.miembrosEquipoData,
    this.jugadorData,
    this.equipoData
  });

}

class ProfilePage extends StatefulWidget {
  // Instanciamos el objeto y lo pasamos al constructor
  int idJugador;
  Jugadors jugador;
  List<Encuentros> encuentros;
  List<Jugadors> miembrosEquipo;
  Equipos equipo;
  Future<ProfileData> data;



  ProfilePage(this.idJugador, this.encuentros,
      {Key key, this.title})
      : super(key: key);
  final String title;

  @override
  _ProfilePageState createState() => _ProfilePageState(
      this.idJugador, this.encuentros, title: 'Meet & Match');
}

class _ProfilePageState extends State<ProfilePage> {

  // Instanciamos el objeto y lo pasamos al constructor
  int idJugador;
  Jugadors jugador;
  List<Encuentros> encuentros;
  List<Jugadors> miembrosEquipo;
  Equipos equipo;
  Future<ProfileData> data;
  ProfileData data2;

  _ProfilePageState(
      this.idJugador, this.encuentros, {Key key, this.title})
      : super();
  final String title;

  Future<ProfileData> _fetchAllData() async {
    return ProfileData(
        miembrosEquipoData: await Equipos.getMiembrosEquipoPorIdJugador(this.idJugador.toString()),
        jugadorData: await Jugadors.getJugadors(this.idJugador.toString()),
        equipoData: await Equipos.getEquipoJugador(this.idJugador.toString())
    );
  }

  @override
  void initState(){
    super.initState();
    setState(() {
      data = _fetchAllData();
    });
    for(int i =0; i < encuentros.length; i++){
      if(encuentros[i].usuario_id != this.idJugador)
        encuentros.removeAt(i);
    }
  }


  @override
  Widget build(BuildContext context) {
    int _value = 1;
    return Scaffold(
      appBar: AppBar(
        title: Text('Meet & Match'),
      ),

      body: Container(
        decoration: BoxDecoration(
            gradient: LinearGradient(begin:Alignment.topLeft, end: Alignment.bottomRight, colors:[Colors.white, Colors.white])
        ),
        child: FutureBuilder<ProfileData>(
          future: data,
          builder: (context, snapshot) {
            // If the connection is done,
            // check for response data or an error.
            if (snapshot.connectionState == ConnectionState.done) {
              if (snapshot.hasData) {
                data2= snapshot.data;
                jugador= snapshot.data.jugadorData;
                miembrosEquipo= snapshot.data.miembrosEquipoData;
                equipo= snapshot.data.equipoData;
                return Column(
                  children: <Widget>[
                    Padding(
                      padding: EdgeInsets.fromLTRB(30, 50, 30, 30),
                      child: Row(
                        mainAxisAlignment: MainAxisAlignment.spaceBetween,
                        children: <Widget>[
                          Padding( padding: EdgeInsets.only(left: 135),
                              child: Text('Perfil de\n'+
                                  this.jugador.nick,
                                style: TextStyle(fontSize: 18, fontWeight: FontWeight.bold, color: Colors.indigo), textAlign: TextAlign.center,
                              )
                          ),
                          Container(height: 24, width: 24)
                        ],
                      ),
                    ),
                    Expanded(
                        child: SingleChildScrollView( child:
                        Container(
                          child: Column(
                            children: <Widget>[
                              Padding(
                                padding: const EdgeInsets.fromLTRB(20, 25, 20, 4),
                                child: Container(
                                  height: 60,
                                  child: Align(
                                    alignment: Alignment.centerLeft,
                                    child: Padding(
                                      padding: const EdgeInsets.all(8.0),
                                      child: Text(
                                        'Nombre: ' + this.jugador.nombreCompleto,
                                        style: TextStyle(color: Colors.black),
                                      ),
                                    ),
                                  ),
                                  decoration: BoxDecoration(
                                      borderRadius: BorderRadius.all(Radius.circular(20)),
                                      border: Border.all(width: 1.0, color: Colors.indigo)),
                                ),
                              ),
                              Padding(
                                padding: const EdgeInsets.fromLTRB(20, 5, 20, 4),
                                child: Container(
                                  height: 60,
                                  child: Align(
                                    alignment: Alignment.centerLeft,
                                    child: Padding(
                                      padding: const EdgeInsets.all(8.0),
                                      child: Text(
                                        'Edad: ' + this.jugador.edad.toString(),
                                        style: TextStyle(color: Colors.black),
                                      ),
                                    ),
                                  ),
                                  decoration: BoxDecoration(
                                      borderRadius: BorderRadius.all(Radius.circular(20)),
                                      border: Border.all(width: 1.0, color: Colors.indigo)),
                                ),
                              ),
                              Padding(
                                padding: const EdgeInsets.fromLTRB(20, 5, 20, 4),
                                child: Container(
                                  height: 60,
                                  child: Align(
                                    alignment: Alignment.centerLeft,
                                    child: Padding(
                                        padding: const EdgeInsets.all(8.0),
                                        child: (this.data2.equipoData== null) ? Text(
                                          'Equipo: Sin equipo',
                                          style: TextStyle(color: Colors.black),
                                        ) : Text(
                                          'Equipo: ' + this.equipo.Nombreequipo.toString() + '  ('+ this.equipo.Deporte.toString() +')',
                                          style: TextStyle(color: Colors.black),
                                        )
                                    ),
                                  ),
                                  decoration: BoxDecoration(
                                      borderRadius: BorderRadius.all(Radius.circular(20)),
                                      border: Border.all(width: 1.0, color: Colors.indigo)),
                                ),
                              ),
                              if(this.data2.equipoData != null)
                                Padding(
                                  padding: const EdgeInsets.fromLTRB(20, 5, 20, 4),
                                  child: Text(
                                    'Miembros',
                                    style: TextStyle(color: Colors.indigo),
                                  ),
                                ),
                              if(this.data2.equipoData != null)
                                Padding(
                                  padding: const EdgeInsets.fromLTRB(20, 5, 20, 4),
                                  child: Container(
                                    height: 150,
                                    child: Align(
                                      alignment: Alignment.centerLeft,
                                      child: Padding(
                                        padding: const EdgeInsets.all(8.0),
                                        child: (this.data2.equipoData== null) ? Text("") :
                                        ListView.builder(
                                          itemCount: miembrosEquipo.length,
                                          itemBuilder: (context, index){
                                            return ListTile(
                                              title: Text('${miembrosEquipo[index].nick}'),
                                              leading: CircleAvatar(
                                                backgroundImage: NetworkImage(
                                                  'https://i.pinimg.com/originals/7d/eb/0d/7deb0db7a4928366eab74e5a09bb24f2.png',
                                                ),),
                                            );
                                          },
                                        ),
                                      ),
                                    ),
                                    decoration: BoxDecoration(
                                        borderRadius: BorderRadius.all(Radius.circular(20)),
                                        border: Border.all(width: 1.0, color: Colors.indigo)),
                                  ),
                                ),
                              if(this.encuentros != null)
                                Padding(
                                  padding: const EdgeInsets.fromLTRB(20, 5, 20, 4),
                                  child: Text(
                                    'Encuentros',
                                    style: TextStyle(color: Colors.indigo),
                                  ),
                                ),
                              if(this.encuentros != null)
                                Padding(
                                  padding: const EdgeInsets.fromLTRB(20, 5, 20, 4),
                                  child: Container(
                                    height: 400,
                                    child: Align(
                                      alignment: Alignment.centerLeft,
                                      child: Padding(
                                        padding: const EdgeInsets.all(8.0),
                                        child:
                                        ListView.builder(
                                          itemCount: encuentros.length,
                                          itemBuilder: (context, index){
                                            return ListTile(
                                              title: Text('${encuentros[index].deporte + ' | '+
                                                  encuentros[index].fecha + ' | ' +
                                                  encuentros[index].ubicacion}'),
                                              subtitle: Text(encuentros[index].tiempo.toString() + ' min | ' +
                                                  encuentros[index].numperson.toString() + ' personas' ),
                                              leading: CircleAvatar(
                                                child: Text(encuentros[index].id.toString()),
                                              ),
                                            );
                                          },
                                        ),

                                      ),
                                    ),

                                    decoration: BoxDecoration(
                                        borderRadius: BorderRadius.all(Radius.circular(20)),
                                        border: Border.all(width: 1.0, color: Colors.indigo)),
                                  ),
                                ),

                            ],
                          ),
                        ),
                        ))
                  ],
                );

              } else if (snapshot.hasError) {
                return Text("${snapshot.error}");
              }
            }
            // By default, show a loading spinner.
            return Text("");
          },
        ),
      ),
    );
  }
}


class MySecondPage extends StatefulWidget {
  // Instanciamos el objeto y lo pasamos al constructor
  Objetivo target;
  Alquileres alquileres;
  PagoPaypal paypal;
  PagoTarjeta tarjeta;
  PagoTransferencia trans;
  int idUserLogin;

  MySecondPage(this.idUserLogin,
      this.target, this.alquileres, this.paypal, this.tarjeta, this.trans,
      {Key key, this.title})
      : super(key: key);
  final String title;

  int getIdUser(){
    return idUserLogin;
  }

  @override
  _MySecondPageState createState() => _MySecondPageState(this.idUserLogin,
      this.target, this.alquileres, this.paypal, this.tarjeta, this.trans);
}

void showAlert(BuildContext context) {
  showDialog(
      context: context,
      builder: (context) => AlertDialog(
            title: Text("Error al realizar el alquiler"),
            content: Text(
                "La ubicación elegida ya ha sido reservada en la fecha escogida, por favor eliga otra"),
            actions: [
              RaisedButton(
                child: Text('OK'),
                onPressed: () {
                  Navigator.of(context).pop();
                },
              ),
            ],
          ));
}

void loginError(BuildContext context){
  showDialog(
      context: context,
      builder: (context) => AlertDialog(
        title: Text("Error al realizar el login"),
        content: Text(
            "Usuario o contraseña incorrectos"),
        actions: [
          RaisedButton(
            child: Text('OK'),
            onPressed: () {
              Navigator.of(context).pop();
            },
          ),
        ],
      ));
}

void errorAlquilar(BuildContext context) {
  showDialog(
      context: context,
      builder: (context) => AlertDialog(
            title: Text("Todos los campos deben estar rellenos"),
            content: Text(
                "Para realizar el alquiler debe completar todos los campos"),
            actions: [
              RaisedButton(
                child: Text('OK'),
                onPressed: () {
                  Navigator.of(context).pop();
                },
              ),
            ],
          ));
}

class _MySecondPageState extends State<MySecondPage> {
  // Instanciamos el objeto y lo pasamos al constructor
  Objetivo target;
  Alquileres alquileres;
  PagoPaypal paypal;
  PagoTarjeta tarjeta;
  PagoTransferencia trans;
  int idUserLogin;

  _MySecondPageState(this.idUserLogin,
      this.target, this.alquileres, this.paypal, this.tarjeta, this.trans)
      : super();
  final myController1 = TextEditingController();
  final myController2 = TextEditingController();
  final myController3 = TextEditingController();

  List<String> _deportes = ["Futbol", "Baloncesto", "Volleyball"];
  //String deporte;
  String deporte = 'Futbol';
  List _horas = ["30", "45", "60", "75", "90", "105", "120"];
  //String hora;
  String hora = '30';
  List _pagos = ["PayPal", "Tarjeta", "Transferencia"];
  //String pago;
  String pago = 'PayPal';
  @override
  void dispose() {
    myController1.dispose();
    myController2.dispose();
    myController3.dispose();
    super.dispose();
  }

  @override
  Widget build(BuildContext context) {
    int _value = 1;
    return Scaffold(
      appBar: AppBar(
        title: Text('Meet & Match'),
      ),
      body: Center(
        child: SingleChildScrollView(
          child: Column(
            mainAxisAlignment: MainAxisAlignment.center,
            children: <Widget>[
              Padding(
                padding: const EdgeInsets.all(20.0),
                child: DropdownButtonFormField(
                  key: Key('deporte'),
                  decoration: InputDecoration(
                    border: OutlineInputBorder(
                      borderRadius: const BorderRadius.all(
                        const Radius.circular(30.0),
                      ),
                    ),
                  ),
                  focusColor: Colors.red,
                  hint: Text('Elige un deporte'),
                  dropdownColor: Colors.grey,
                  elevation: 5,
                  icon: Icon(Icons.arrow_drop_down),
                  iconSize: 36.0,
                  isExpanded: false,
                  value: deporte,
                  onChanged: (value) {
                    setState(() {
                      deporte = value;
                    });
                  },
                  items: _deportes.map((value) {
                    return DropdownMenuItem(
                      value: value,
                      child: Text(value),
                    );
                  }).toList(),
                ),
              ),
              Padding(
                padding: const EdgeInsets.all(20.0),
                child: new TextField(
                  key: Key('ubicacion'),
                  controller: myController1,
                  decoration: new InputDecoration(
                      filled: true,
                      labelText: 'Ubicación',
                      border: OutlineInputBorder(),
                      hintText: 'Escriba la ubicación aqui...'),
                ),
              ),
              Padding(
                  padding: const EdgeInsets.all(20.0),
                  child: new TextField(
                    key: Key('fecha_alquiler'),
                    controller: myController2,
                    decoration: new InputDecoration(
                        filled: true,
                        labelText: 'Fecha',
                        border: OutlineInputBorder(),
                        hintText: 'Formato fecha: dd/mm/yy hh:mm'),
                  )),
              Padding(
                padding: const EdgeInsets.all(20.0),
                child: DropdownButtonFormField(
                  decoration: InputDecoration(
                    border: OutlineInputBorder(
                      borderRadius: const BorderRadius.all(
                        const Radius.circular(30.0),
                      ),
                    ),
                  ),
                  focusColor: Colors.red,
                  hint: Text('Elige el tiempo en minutos'),
                  dropdownColor: Colors.grey,
                  elevation: 5,
                  icon: Icon(Icons.arrow_drop_down),
                  iconSize: 36.0,
                  isExpanded: false,
                  value: hora,
                  onChanged: (value) {
                    setState(() {
                      hora = value;
                    });
                  },
                  items: _horas.map((value) {
                    return DropdownMenuItem(
                      value: value,
                      child: Text(value),
                    );
                  }).toList(),
                ),
              ),
              Padding(
                  padding: const EdgeInsets.all(20.0),
                  child: new TextField(
                    key: Key('npersonas'),
                    controller: myController3,
                    decoration: new InputDecoration(
                        filled: true,
                        labelText: 'Nº personas',
                        border: OutlineInputBorder(),
                        hintText:
                            'Escriba el numero de personas para el encuentro...'),
                  )),
              Padding(
                padding: const EdgeInsets.all(20.0),
                child: DropdownButtonFormField(
                  decoration: InputDecoration(
                    border: OutlineInputBorder(
                      borderRadius: const BorderRadius.all(
                        const Radius.circular(30.0),
                      ),
                    ),
                  ),
                  focusColor: Colors.red,
                  hint: Text('Elige el método de pago'),
                  dropdownColor: Colors.grey,
                  elevation: 5,
                  icon: Icon(Icons.arrow_drop_down),
                  iconSize: 36.0,
                  isExpanded: false,
                  value: pago,
                  onChanged: (value) {
                    setState(() {
                      pago = value;
                      //metodoPago = value;
                    });
                  },
                  items: _pagos.map((value) {
                    return DropdownMenuItem(
                      value: value,
                      child: Text(value),
                    );
                  }).toList(),
                ),
              ),
              Row(
                mainAxisAlignment: MainAxisAlignment.spaceEvenly,
                children: <Widget>[
                  RaisedButton(
                      key: Key('Alquilar'),
                      child: Text('Alquilar'),
                      onPressed: () {
                        if (myController1.text == '' ||
                            myController2.text == '' ||
                            myController3.text == '' ||
                            pago == null ||
                            deporte == null ||
                            hora == null) {
                          errorAlquilar(context);
                        } else {
                          Cliente client = new Cliente();
                          Alquiler alq = new Alquiler();
                          GestorFiltros gestor = new GestorFiltros();

                          alq.setAlquiler(
                              5.0,
                              deporte,
                              int.parse(hora),
                              int.parse(myController3.text),
                              myController1.text,
                              myController2.text);
                          client.setAlquiler(alq);
                          gestor.filtrar(client.getAlquiler());

                          if (alquileres.existeReserva(
                                  myController1.text, myController2.text) ==
                              true) {
                            showAlert(context);
                          } else {
                            double precio = client.getAlquiler().getPrecio();
                            alquileres.setNuevoAlquiler(alq);
                            target.nuevoAlquiler(alq);
                            alquileres.muestraAlquileres();

                            int tiempo = int.parse(hora);
                            int numperson = int.parse(myController3.text);
                            String ubicacion = myController1.text;
                            String fecha = myController2.text;

                            if (pago == "PayPal") {
                              Navigator.push(
                                context,
                                MaterialPageRoute(
                                    builder: (context) =>
                                        PagoPayPalInt(this.deporte, fecha,
                                            tiempo, numperson, this.paypal,
                                            ubicacion, precio,
                                            this.idUserLogin)),
                              );
                            } else if (pago == "Tarjeta") {
                              Navigator.push(
                                context,
                                MaterialPageRoute(
                                    builder: (context) =>
                                        PagoTarjetaInt(this.deporte, fecha,
                                            tiempo, numperson, this.tarjeta,
                                            ubicacion, precio,
                                            this.idUserLogin)),
                              );
                            } else if (pago == "Transferencia") {
                              Navigator.push(
                                context,
                                MaterialPageRoute(
                                    builder: (context) => PagoTransferenciaInt(
                                        this.deporte, fecha,
                                        tiempo, numperson, this.trans,
                                        ubicacion, precio,
                                        this.idUserLogin)),
                              );
                            }
                          }
                        }
                      }),
                  RaisedButton(
                    child: Text('Ver Objetivo'),
                    onPressed: () {
                      target.mostrarObjetivo(context);
                    },
                  ),
                ],
              ),
            ],
          ),
        ),
      ),
    );
  }
}

void realizarPago(String usuario, String correo, double pago, BuildContext context) {
  showDialog(
      context: context,
      builder: (context) => AlertDialog(
        title: Text("Su pago ha sido realizado con éxito"),
        content: Text("Se ha completado el cargo de " + pago.toStringAsFixed(2) +
            " euros al usuario de PayPal " + usuario + ", con correo " +
            correo),
        actions: [
          RaisedButton(
            child: Text('OK'),
            onPressed: () {
              Navigator.of(context).pop();
            },
          ),
        ],
      )
  );
}

class PagoPayPalInt extends StatelessWidget {
  // Instanciamos el objeto y lo pasamos al constructor
  String deporte;
  String fecha;
  int tiempo;
  int numperson;
  PagoPaypal paypal;
  String ubicacion;
  double precio;
  int idUserLogin;
  Objetivo target = new Objetivo();
  Alquileres alquileres = new Alquileres();
  PagoTarjeta tarjeta = new PagoTarjeta();
  PagoTransferencia trans = new PagoTransferencia();
  Future<Encuentros> _futureEncuentro;
  Future<List<Encuentros>> _futureList = Encuentros.getAllEncuentros();
  int idEncuentro;
  Future<Apuntados> _futureApuntado;

  final myController1 = TextEditingController();
  final myController2 = TextEditingController();

  PagoPayPalInt(this.deporte, this.fecha, this.tiempo, this.numperson,
  this.paypal, this.ubicacion, this.precio, this.idUserLogin,
      {Key key, this.title})
      : super(key: key);
  final String title;

  @override
  void dispose() {
    myController1.dispose();
    myController2.dispose();
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text('PayPal'),
      ),
      body: SingleChildScrollView(
        child: Column(
          mainAxisAlignment: MainAxisAlignment.center,
          children: <Widget>[
            Container(
              width: 300.0,
                height: 110.0,
                child: Image.network(
                    'https://1000marcas.net/wp-content/uploads/2019/12/PayPal-Logo.png')
            ),
            Container(
              margin: const EdgeInsets.only(top:0.0, left: 10.0, right: 10.0),
              padding: const EdgeInsets.only(bottom: 1.0),
              child: RichText(
                textAlign: TextAlign.center,
                text: TextSpan(
                  text: 'El precio final del alquiler es de '+ precio.toStringAsFixed(2),
                  style:  TextStyle(fontSize: 15.0, color: Colors.black),
                  children: const <TextSpan>[
                    TextSpan(text: ' euros. Has elegido la opción de pago de '
                        'PayPal, por lo que completa los campos a continuación '
                        'para finalizar el pago del alquiler.'),
                  ],
                ),
              ),
            ),
            Container(
                margin: const EdgeInsets.only(bottom: 0.0),
                //padding: const EdgeInsets.only(bottom: 50.0)
              child:Padding(
                  padding: const EdgeInsets.all(20.0),
                  child: new TextField(
                    key: Key('usuario'),
                    controller: myController1,
                    decoration: new InputDecoration(
                        filled: true,
                        labelText: 'Nombre de usuario',
                        border: OutlineInputBorder(),
                        hintText: 'Escribe su nome de usuario de PayPal...'),
                  )),
            ),
            Container(
              //margin: const EdgeInsets.only(bottom: 150.0),
              child:Padding(
                  padding: const EdgeInsets.all(20.0),
                  child: new TextField(
                    key: Key('correo'),
                    controller: myController2,
                    decoration: new InputDecoration(
                        filled: true,
                        labelText: 'Correo Electrónico',
                        border: OutlineInputBorder(),
                        hintText: 'Escriba su correo electrónico...'),
                  )),
            ),
            Container(
              margin: const EdgeInsets.only(top: 20.0),
              child: Row(
                mainAxisAlignment: MainAxisAlignment.spaceEvenly,
                children: <Widget>[
                  new RaisedButton(
                    child: Text('Efectuar pago'),
                    onPressed: () {
                      realizarPago(myController1.text, myController2.text, precio, context);
                      _futureEncuentro = Encuentros.createEncuentro(deporte, fecha, tiempo, numperson, 'PayPal', ubicacion, precio.toInt(), idUserLogin);
                    },
                  ),
                  new RaisedButton(
                    child: Text('Volver a homepage'),
                    onPressed: () {
                      _futureApuntado = Apuntados.createApuntado(idUserLogin, idEncuentro);
                      Navigator.push(
                          context,
                          MaterialPageRoute(
                              builder: (_) => HomePage(idUserLogin,target,
                                  alquileres, paypal, tarjeta, trans,
                                  title: 'Meet & Match'))
                      );
                    },
                  ),
                ],
              ),
            ),
            FutureBuilder<List<Encuentros>>(
              future: _futureList,
              builder: (context, snapshot) {
                // If the connection is done,
                // check for response data or an error.
                if (snapshot.connectionState == ConnectionState.done) {
                  if (snapshot.hasData) {
                    idEncuentro = snapshot.data[snapshot.data.length-1].id +1;
                  } else if (snapshot.hasError) {
                    return Text("${snapshot.error}");
                  }
                }
                // By default, show a loading spinner.
                return Text("");
              },
            ),
          ],
        ),
      ),
    );
  }
}

class PagoTarjetaInt extends StatelessWidget {
  // Instanciamos el objeto y lo pasamos al constructor
  String deporte;
  String fecha;
  int tiempo;
  int numperson;
  PagoPaypal paypal;
  PagoTarjeta tarjeta;
  String ubicacion;
  double precio;
  int idUserLogin;
  Objetivo target = new Objetivo();
  Alquileres alquileres = new Alquileres();
  PagoTransferencia trans = new PagoTransferencia();
  Future<Encuentros> _futureEncuentro;
  Future<List<Encuentros>> _futureList = Encuentros.getAllEncuentros();
  int idEncuentro;
  Future<Apuntados> _futureApuntado;

  final myController1 = TextEditingController();
  final myController2 = TextEditingController();
  final myController3 = TextEditingController();

  PagoTarjetaInt(this.deporte, this.fecha, this.tiempo, this.numperson,
      this.tarjeta, this.ubicacion, this.precio, this.idUserLogin,
      {Key key, this.title})
      : super(key: key);
  final String title;

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text('Tarjeta'),
      ),
      body: SingleChildScrollView(
        child: Column(
          mainAxisAlignment: MainAxisAlignment.center,
          children: <Widget>[
            Container(
                width: 300.0,
                height: 110.0,
                child: Image.network(
                    'https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcQfAD2jPRR_Ez81JqZjwUHovGfcNK6UYFHbFGXezTz8DAUa-yKydNZLII9DZfOWgNsLMmQ&usqp=CAU')
            ),
            Container(
              margin: const EdgeInsets.only(top:0.0, left: 10.0, right: 10.0),
              padding: const EdgeInsets.only(bottom: 1.0),
              child: RichText(
                textAlign: TextAlign.center,
                text: TextSpan(
                  text: 'El precio final del alquiler es de '+ precio.toStringAsFixed(2),
                  style:  TextStyle(fontSize: 15.0, color: Colors.black),
                  children: const <TextSpan>[
                    TextSpan(text: ' euros. Has elegido la opción de pago de '
                        ' con Tarjeta, por lo que completa los campos a continuación '
                        'para finalizar el pago del alquiler.'),
                  ],
                ),
              ),
            ),
            Container(
              child:Padding(
                  padding: const EdgeInsets.all(20.0),
                  child: new TextField(
                    key: Key('numero'),
                    controller: myController1,
                    decoration: new InputDecoration(
                        filled: true,
                        labelText: 'Número de la tarjeta',
                        border: OutlineInputBorder(),
                        hintText: 'Escribe el número de la tarjeta...'),
                  )),
            ),
            Container(
              child: Padding(
                  padding: const EdgeInsets.all(20.0),
                  child: new TextField(
                    key: Key('fecha'),
                    controller: myController2,
                    decoration: new InputDecoration(
                        filled: true,
                        labelText: 'Fecha caducidad',
                        border: OutlineInputBorder(),
                        hintText: 'Fecha estilo mm/yy...'),
                  )),
            ),
            Container(
              child: Padding(
                  padding: const EdgeInsets.all(20.0),
                  child: new TextField(
                    key: Key('seguridad'),
                    controller: myController3,
                    decoration: new InputDecoration(
                        filled: true,
                        labelText: 'Número de seguridad',
                        border: OutlineInputBorder(),
                        hintText:
                        'Escriba el número de seguridad de su tarjeta...'),
                  )),

            ),
            Container(
              margin: const EdgeInsets.only(top: 20.0),
              child: Row(
                mainAxisAlignment: MainAxisAlignment.spaceEvenly,
                children: <Widget>[
                  new RaisedButton(
                    child: Text('Efectuar pago'),
                    onPressed: () {
                      realizarPago(myController1.text, myController2.text, precio, context);
                      _futureEncuentro = Encuentros.createEncuentro(deporte, fecha, tiempo, numperson, 'Tarjeta', ubicacion, precio.toInt(), idUserLogin);
                    },
                  ),
                  new RaisedButton(
                    child: Text('Volver a homepage'),
                    onPressed: () {
                      _futureApuntado = Apuntados.createApuntado(idUserLogin, idEncuentro);
                      Navigator.push(
                          context,
                          MaterialPageRoute(
                              builder: (_) => HomePage(idUserLogin,target,
                                  alquileres, paypal, tarjeta, trans,
                                  title: 'Meet & Match'))
                      );
                    },
                  ),
                ],
              ),
            ),
            FutureBuilder<List<Encuentros>>(
              future: _futureList,
              builder: (context, snapshot) {
                // If the connection is done,
                // check for response data or an error.
                if (snapshot.connectionState == ConnectionState.done) {
                  if (snapshot.hasData) {
                    idEncuentro = snapshot.data[snapshot.data.length-1].id +1;
                  } else if (snapshot.hasError) {
                    return Text("${snapshot.error}");
                  }
                }
                // By default, show a loading spinner.
                return Text("");
              },
            ),
          ],
        ),
      ),
    );
  }
}

class PagoTransferenciaInt extends StatelessWidget {
  // Instanciamos el objeto y lo pasamos al constructor
  String deporte;
  String fecha;
  int tiempo;
  int numperson;
  PagoPaypal paypal;
  PagoTransferencia trans;
  String ubicacion;
  double precio;
  int idUserLogin;
  Objetivo target = new Objetivo();
  Alquileres alquileres = new Alquileres();
  PagoTarjeta tarjeta = new PagoTarjeta();
  Future<Encuentros> _futureEncuentro;
  Future<List<Encuentros>> _futureList = Encuentros.getAllEncuentros();
  int idEncuentro;
  Future<Apuntados> _futureApuntado;

  final myController1 = TextEditingController();
  final myController2 = TextEditingController();

  PagoTransferenciaInt(this.deporte, this.fecha, this.tiempo, this.numperson,
      this.trans, this.ubicacion, this.precio, this.idUserLogin,
      {Key key, this.title})
      : super(key: key);
  final String title;

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text('Transferencia'),
      ),
      body: SingleChildScrollView(
        child: Column(
          mainAxisAlignment: MainAxisAlignment.center,
          children: <Widget>[
            Container(
                width: 300.0,
                height: 110.0,
                child: Image.network(
                    'https://www.jokerbet.es/img/logos/pasarelas/transferencia-bancaria2.png')
            ),
            Container(
              margin: const EdgeInsets.only(top:0.0, left: 10.0, right: 10.0),
              padding: const EdgeInsets.only(bottom: 1.0),
              child: RichText(
                textAlign: TextAlign.center,
                text: TextSpan(
                  text: 'El precio final del alquiler es de '+ precio.toStringAsFixed(2),
                  style:  TextStyle(fontSize: 15.0, color: Colors.black),
                  children: const <TextSpan>[
                    TextSpan(text: ' euros. Has elegido la opción de pago por '
                        'transferencia, por lo que completa los campos a continuación '
                        'para finalizar el pago del alquiler.'),
                  ],
                ),
              ),
            ),
            Container(
              margin: const EdgeInsets.only(bottom: 0.0),
              //padding: const EdgeInsets.only(bottom: 50.0)
              child:Padding(
                  padding: const EdgeInsets.all(20.0),
                  child: new TextField(
                    controller: myController1,
                    decoration: new InputDecoration(
                        filled: true,
                        labelText: 'Nombre del titural de la cuenta',
                        border: OutlineInputBorder(),
                        hintText: 'Escribe el nombre del titular...'),
                  )),
            ),
            Container(
              //margin: const EdgeInsets.only(bottom: 150.0),
              child:Padding(
                  padding: const EdgeInsets.all(20.0),
                  child: new TextField(
                    controller: myController2,
                    decoration: new InputDecoration(
                        filled: true,
                        labelText: 'Número de la cuenta bancaria',
                        border: OutlineInputBorder(),
                        hintText: 'Escribe el número de la cuenta...'),
                  )),
            ),
            Container(
              margin: const EdgeInsets.only(top: 20.0),
              child: Row(
                mainAxisAlignment: MainAxisAlignment.spaceEvenly,
                children: <Widget>[
                  new RaisedButton(
                    child: Text('Efectuar pago'),
                    onPressed: () {
                      realizarPago(myController1.text, myController2.text, precio, context);
                      _futureEncuentro = Encuentros.createEncuentro(deporte, fecha, tiempo, numperson, 'Transferencia', ubicacion, precio.toInt(), idUserLogin);
                    },
                  ),
                  new RaisedButton(
                    child: Text('Volver a homepage'),
                    onPressed: () {
                      _futureApuntado = Apuntados.createApuntado(idUserLogin, idEncuentro);
                      Navigator.push(
                          context,
                          MaterialPageRoute(
                              builder: (_) => HomePage(idUserLogin,target,
                                  alquileres, paypal, tarjeta, trans,
                                  title: 'Meet & Match'))
                      );
                    },
                  ),
                ],
              ),
            ),
            FutureBuilder<List<Encuentros>>(
              future: _futureList,
              builder: (context, snapshot) {
                // If the connection is done,
                // check for response data or an error.
                if (snapshot.connectionState == ConnectionState.done) {
                  if (snapshot.hasData) {
                    idEncuentro = snapshot.data[snapshot.data.length-1].id +1;
                  } else if (snapshot.hasError) {
                    return Text("${snapshot.error}");
                  }
                }
                // By default, show a loading spinner.
                return Text("");
              },
            ),
          ],
        ),
      ),
    );
  }
}

class ApuntarseEncuentro extends StatelessWidget {
  int idUserLogin;
  Future<List<Encuentros>> _futureList = Encuentros.getAllEncuentros();
  Future<Apuntados> _futureApuntado;
  List<Encuentros> encuentros = [];
  final myController1 = TextEditingController();

  ApuntarseEncuentro(this.idUserLogin, this.encuentros, {Key key, this.title})
      : super(key: key);
  final String title;

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text('Apuntarse a encuentro'),
      ),
      body: ListView.builder(
              itemCount: encuentros.length +1,
              itemBuilder: (context, index){
                return (index == encuentros.length ) ?
                Container(
                  margin: const EdgeInsets.only(top: 20.0),
                  child: Column(
                    mainAxisAlignment: MainAxisAlignment.spaceEvenly,
                    children: <Widget>[
                      Padding(
                        padding: const EdgeInsets.all(20.0),
                        child: new TextField(
                          key: Key('idEvento'),
                          controller: myController1,
                          decoration: new InputDecoration(
                              filled: true,
                              labelText: 'idEvento',
                              border: OutlineInputBorder(),
                              hintText: 'Escriba la id del evento para apuntarse...'),
                        ),
                      ),
                      new RaisedButton(
                        child: Text('Apuntarse a encuentro'),
                        onPressed: () {
                          bool id = false;
                          for(int i = 0; i < encuentros.length && !id; i++){
                            if(int.parse(myController1.text) == encuentros[i].id){
                              id = true;
                            }
                          }
                          if(id){
                            //_futureApuntado = Apuntados.createApuntado(idUserLogin,
                            // int.parse(myController1.text));
                            realizarApuntado(context, myController1.text);
                          }else {
                            idIncorrecto(context);
                          }
                        },
                      ),
                    ],
                  ),
                )
                    :
                ListTile(
                  title: Text('${encuentros[index].deporte + ' | '+
                      encuentros[index].fecha + ' | ' +
                      encuentros[index].ubicacion}'),
                  subtitle: Text(encuentros[index].tiempo.toString() + ' min | ' +
                      encuentros[index].numperson.toString() + ' personas' ),
                  leading: CircleAvatar(
                    child: Text(encuentros[index].id.toString()),
                  ),
                );
              },
            ),

    );
  }

  void realizarApuntado(BuildContext context, String idEvento) {
    showDialog(
        context: context,
        builder: (context) => AlertDialog(
          title: Text('Se ha apuntado al encuentro ' + idEvento + ' con éxito'),
          content: Text("¡Disfrute de la experiencia!"),
          actions: [
            RaisedButton(
              child: Text('OK'),
              onPressed: () {
                Navigator.of(context).pop();
              },
            ),
          ],
        )
    );
  }

  void idIncorrecto(BuildContext context) {
    showDialog(
        context: context,
        builder: (context) => AlertDialog(
          title: Text('Error al escribir el id del evento'),
          content: Text("El id introducido no existe en la lista de encuentros"),
          actions: [
            RaisedButton(
              child: Text('OK'),
              onPressed: () {
                Navigator.of(context).pop();
              },
            ),
          ],
        )
    );
  }
}