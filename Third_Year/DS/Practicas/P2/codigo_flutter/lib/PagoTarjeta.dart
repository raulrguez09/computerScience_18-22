import 'EstrategiaPago.dart';
import 'package:flutter/material.dart';


class PagoTarjeta implements EstrategiaPago {
  String _num, _fecha, _cod;

  PagoTarjeta(){}

  void setNumero(String n){
    _num = n;
  }

  void setFecha(String f){
    _fecha = f;
  }

  void setCodigo(String c){
    _cod = c;
  }

  void realizarPago(double pago, BuildContext context){
    showAlert(pago, context);
  }

  void showAlert(double pago,BuildContext context) {
    showDialog(
        context: context,
        builder: (context) => AlertDialog(
          title: Text("Su pago ha sido realizado con éxito"),
          content: Text("El cargo de " + pago.toStringAsFixed(2) + " euros ha "
              "sido completado a la tarjeta con numero '" + _num + "', fecha '"
              + _fecha + "', y código ***." ),
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