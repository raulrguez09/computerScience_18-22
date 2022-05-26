import 'EstrategiaPago.dart';
import 'package:flutter/material.dart';

class PagoTransferencia implements EstrategiaPago {
  String _titular, _ncuenta;

  PagoTransferencia(){}

  void setTitular(String t){
    _titular = t;
  }

  void setCuenta(String c){
    _ncuenta = c;
  }

  void realizarPago(double pago, BuildContext context){
    showAlert(pago, context);
  }

  void showAlert(double pago, BuildContext context) {
    showDialog(
        context: context,
        builder: (context) => AlertDialog(
          title: Text("Su pago ha sido realizado con éxito"),
          content: Text("El cargo de " + pago.toStringAsFixed(2) + " euros ha "
          "sido completado, haciendose la transferencia desde la cuenta '" +
              _ncuenta + "' del titular '" + _titular + "'."),
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