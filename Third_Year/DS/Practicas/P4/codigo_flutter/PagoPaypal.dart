import 'EstrategiaPago.dart';
import 'package:flutter/material.dart';

class PagoPaypal implements EstrategiaPago {
  String _correo;
  String _usuario;

  void setCorreo(String c){
    _correo = c;
  }

  void setUsuario(String u){
    _usuario = u;
  }

  void realizarPago(double pago, BuildContext context){
    showAlert(pago, context);
  }

  void showAlert(double pago, BuildContext context) {
    showDialog(
        context: context,
        builder: (context) => AlertDialog(
          title: Text("Su pago ha sido realizado con éxito"),
          content: Text("Se ha completado el cargo de " + pago.toStringAsFixed(2) +
              " euros al usuario de PayPal " + _usuario + ", con correo " +
              _correo),
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

