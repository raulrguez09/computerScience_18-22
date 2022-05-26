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

void main() {
  runApp(MyApp());
}

class MyApp extends StatelessWidget {
  // This widget is the root of your application.
  @override
  Widget build(BuildContext context) {

    // Creamos la instancia del objeto
    Objetivo target = new Objetivo();
    Alquileres alquileres = new Alquileres();
    PagoPaypal paypal = new PagoPaypal();
    PagoTarjeta tarjeta = new PagoTarjeta();
    PagoTransferencia trans = new PagoTransferencia();

    return MaterialApp(
      title: 'Práctica 2: DS',
      theme: ThemeData(
        primarySwatch: Colors.blue,
      ),

      // Modificamos el constructor pasandole el objeto
      home: HomePage(target, alquileres, paypal, tarjeta, trans, title: 'Meet & Match'),
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

  HomePage(this.target, this.alquileres, this.paypal, this.tarjeta, this.trans, {Key key, this.title}) : super(key: key);
  final String title;

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text('Meet & Match'),
      ),
        body: Center(
          child: Column(
            mainAxisAlignment : MainAxisAlignment.center,
            children: <Widget>[
              Image.network('https://www.podoactiva.com/sites/default/files/sport-moments-banner.jpg'),
              RaisedButton(
                child: Text('Alquilar'),
                onPressed: () {
                  Navigator.push(
                    context,
                    MaterialPageRoute(builder: (context) => MySecondPage(this.target, this.alquileres, this.paypal, this.tarjeta, this.trans)),
                  );
                },
              ),
            ],
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

  MySecondPage(this.target, this.alquileres, this.paypal, this.tarjeta, this.trans, {Key key, this.title}) : super(key: key);
  final String title;

  @override
  _MySecondPageState createState() => _MySecondPageState(this.target, this.alquileres, this.paypal, this.tarjeta, this.trans);
}

void showAlert(BuildContext context) {
  showDialog(
      context: context,
      builder: (context) => AlertDialog(
        title: Text("Error al realizar el alquiler"),
        content: Text("La ubicación elegida ya ha sido reservada en la fecha escogida, por favor eliga otra"),
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

class _MySecondPageState extends State<MySecondPage> {
  // Instanciamos el objeto y lo pasamos al constructor
  Objetivo target;
  Alquileres alquileres;
  PagoPaypal paypal;
  PagoTarjeta tarjeta;
  PagoTransferencia trans;

  _MySecondPageState(this.target, this.alquileres, this.paypal, this.tarjeta, this.trans) : super();
  final myController1 = TextEditingController();
  final myController2 = TextEditingController();
  final myController3 = TextEditingController();


  List _deportes = ["Futbol", "Baloncesto", "Volleyball"];
  String deporte;
  List _horas = ["30", "45", "60", "75", "90", "105", "120"];
  String hora;
  List _pagos = ["PayPal", "Tarjeta", "Transferencia"];
  String pago, metodoPago;

  @override
  void dispose() {
    myController1.dispose();
    myController2.dispose();
    myController3.dispose();
    super.dispose();
  }

  // TITULO
  Widget titleSection=Container(
    child: Column(
      mainAxisAlignment: MainAxisAlignment.spaceAround,
      children: <Widget>[
        Padding(
          padding: const EdgeInsets.all(8.0),
          child: Text(
            'puta',
            style: TextStyle(
              color: Colors.red,
              fontWeight: FontWeight.bold,
              fontSize: 30.0,
            ),
          )
        ),
      ],
    )
  );

  @override
  Widget build(BuildContext context) {
    int _value = 1;
    return Scaffold(
      appBar: AppBar(
        title: Text('Meet & Match'),
      ),
      body: Center(
        child: Column(
          mainAxisAlignment : MainAxisAlignment.center,
          children: <Widget>[
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
                    child: Text(value),);
                }).toList(),
              ),
            ),
            Padding(
                padding: const EdgeInsets.all(20.0),
                child: new TextField(
                  controller: myController1,
                  decoration: new InputDecoration(
                      filled: true,
                      labelText: 'Ubicación',
                      border: OutlineInputBorder(),
                      hintText: 'Escriba la ubicación aqui...'
                  ),
                ),
            ),
            Padding(
                padding: const EdgeInsets.all(20.0),
                child: new TextField(
                  controller: myController2,
                  decoration: new InputDecoration(
                      filled: true,
                      labelText: 'Fecha',
                      border: OutlineInputBorder(),
                      hintText: 'Formato fecha: dd/mm/yy hh:mm'),
                )
            ),
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
                    child: Text(value),);
                }).toList(),
              ),
            ),
            Padding(
                padding: const EdgeInsets.all(20.0),
                child: new TextField(
                  controller: myController3,
                  decoration: new InputDecoration(
                      filled: true,
                      labelText: 'Nº personas',
                      border: OutlineInputBorder(),
                      hintText: 'Escriba el numero de personas para el encuentro...'),
                )
            ),
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
                    child: Text(value),);
                }).toList(),
              ),
            ),
            Row(
              mainAxisAlignment: MainAxisAlignment.spaceEvenly,
              children: <Widget>[
                RaisedButton(
                  child: Text('Alquilar'),
                  onPressed: () {
                    Cliente client = new Cliente();
                    Alquiler alq = new Alquiler();
                    GestorFiltros gestor = new GestorFiltros();

                    alq.setAlquiler(5.0, deporte, int.parse(hora), int.parse(myController3.text), myController1.text, myController2.text);
                    client.setAlquiler(alq);
                    gestor.filtrar(client.getAlquiler());

                    if(alquileres.existeReserva(myController1.text, myController2.text) == true){
                      showAlert(context);
                    }
                    else{
                      double precio = client.getAlquiler().getPrecio();
                      alquileres.setNuevoAlquiler(alq);
                      target.nuevoAlquiler(alq);
                      alquileres.muestraAlquileres();
                      if(pago == "PayPal"){
                        Navigator.push(
                          context,
                          MaterialPageRoute(builder: (context) => PagoPayPalInt(precio, this.paypal)),
                        );
                      }
                      else if(pago == "Tarjeta"){
                        Navigator.push(
                          context,
                          MaterialPageRoute(builder: (context) => PagoTarjetaInt(precio, this.tarjeta)),
                        );
                      }
                      else if(pago == "Transferencia"){
                        Navigator.push(
                          context,
                          MaterialPageRoute(builder: (context) => PagoTransferenciaInt(precio, this.trans)),
                        );
                      }
                    }
                  },
                ),
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
    );
  }
}

class PagoPayPalInt extends StatelessWidget {
  // Instanciamos el objeto y lo pasamos al constructor
  PagoPaypal paypal;
  double precio;
  final myController1 = TextEditingController();
  final myController2 = TextEditingController();

  PagoPayPalInt(this.precio, this.paypal, {Key key, this.title}) : super(key: key);
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
      body: Center(
        child: Column(
          mainAxisAlignment : MainAxisAlignment.center,
          children: <Widget>[
            Text(" El precio final del alquiler es de " +
                precio.toStringAsFixed(2) + " euros. Has elegido la opción de "
                "pago de 'PayPal', por lo que completa los campos a continuación"
                " para finalizar el pago del alquiler"),
            Padding(
                padding: const EdgeInsets.all(20.0),
                child: new TextField(
                  controller: myController1,
                  decoration: new InputDecoration(
                      filled: true,
                      labelText: 'Nombre de usuario',
                      border: OutlineInputBorder(),
                      hintText: 'Escribe su nome de usuario de PayPal...'),
                )
            ),
            Padding(
                padding: const EdgeInsets.all(20.0),
                child: new TextField(
                  controller: myController2,
                  decoration: new InputDecoration(
                      filled: true,
                      labelText: 'Correo Electrónico',
                      border: OutlineInputBorder(),
                      hintText: 'Escriba su correo electrónico...'),
                )
            ),
            RaisedButton(
              child: Text('Efectuar pago'),
              onPressed: () {
                paypal.setUsuario(myController1.text);
                paypal.setCorreo(myController2.text);
                paypal.realizarPago(precio, context);
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
  PagoTarjeta tarjeta;
  double precio;
  final myController1 = TextEditingController();
  final myController2 = TextEditingController();
  final myController3 = TextEditingController();

  PagoTarjetaInt(this.precio, this.tarjeta, {Key key, this.title}) : super(key: key);
  final String title;

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text('Tarjeta'),
      ),
      body: Center(
        child: Column(
          mainAxisAlignment : MainAxisAlignment.center,
          children: <Widget>[
            Text(" El precio final del alquiler es de " +
                precio.toStringAsFixed(2) + " euros. Has elegido la opción de "
                "pago con 'Tarjeta', por lo que completa los campos a continuación"
                " para finalizar el pago del alquiler"),
            Padding(
                padding: const EdgeInsets.all(20.0),
                child: new TextField(
                  controller: myController1,
                  decoration: new InputDecoration(
                      filled: true,
                      labelText: 'Número de la tarjeta',
                      border: OutlineInputBorder(),
                      hintText: 'Escribe el número de la tarjeta...'),
                )
            ),
            Padding(
                padding: const EdgeInsets.all(20.0),
                child: new TextField(
                  controller: myController2,
                  decoration: new InputDecoration(
                      filled: true,
                      labelText: 'Fecha caducidad',
                      border: OutlineInputBorder(),
                      hintText: 'Fecha estilo mm/yy...'),
                )
            ),
            Padding(
                padding: const EdgeInsets.all(20.0),
                child: new TextField(
                  controller: myController3,
                  decoration: new InputDecoration(
                      filled: true,
                      labelText: 'Número de seguridad',
                      border: OutlineInputBorder(),
                      hintText: 'Escriba el número de seguridad de su tarjeta...'),
                )
            ),
            RaisedButton(
              child: Text('Efectuar pago'),
              onPressed: () {
                tarjeta.setNumero(myController1.text);
                tarjeta.setFecha(myController2.text);
                tarjeta.setCodigo(myController3.text);
                tarjeta.realizarPago(precio, context);
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
  PagoTransferencia trans;
  double precio;
  final myController1 = TextEditingController();
  final myController2 = TextEditingController();

  PagoTransferenciaInt(this.precio, this.trans, {Key key, this.title}) : super(key: key);
  final String title;

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text('Transferencia'),
      ),
      body: Center(
        child: Column(
          mainAxisAlignment : MainAxisAlignment.center,
          children: <Widget>[
            Text(" El precio final del alquiler es de " +
                precio.toStringAsFixed(2) + " euros. Has elegido la opción de "
                "pago por 'Transferencia', por lo que completa los campos a continuación"
                " para finalizar el pago del alquiler"),
            Padding(
                padding: const EdgeInsets.all(20.0),
                child: new TextField(
                  controller: myController1,
                  decoration: new InputDecoration(
                      filled: true,
                      labelText: 'Nombre del titural de la cuenta',
                      border: OutlineInputBorder(),
                      hintText: 'Escribe el nombre del titular...'),
                )
            ),
            Padding(
                padding: const EdgeInsets.all(20.0),
                child: new TextField(
                  controller: myController2,
                  decoration: new InputDecoration(
                      filled: true,
                      labelText: 'Número de la cuenta bancaria',
                      border: OutlineInputBorder(),
                      hintText: 'Escribe el número de la cuenta...'),
                )
            ),
            RaisedButton(
              child: Text('Efectuar pago'),
              onPressed: () {
                trans.setTitular(myController1.text);
                trans.setCuenta(myController2.text);
                trans.realizarPago(precio, context);
              },
            ),
          ],
        ),
      ),
    );
  }
}

