import 'package:ejemplods/Alquileres.dart';
import 'package:ejemplods/Objetivo.dart';
import 'package:ejemplods/PagoPaypal.dart';
import 'package:ejemplods/PagoTarjeta.dart';
import 'package:ejemplods/PagoTransferencia.dart';
import 'package:flutter/material.dart';
import 'package:flutter_test/flutter_test.dart';
import 'package:ejemplods/main.dart';

void main() {
  Objetivo target = new Objetivo();
  Alquileres alquileres = new Alquileres();
  PagoPaypal paypal = new PagoPaypal();
  PagoTarjeta tarjeta = new PagoTarjeta();
  PagoTransferencia trans = new PagoTransferencia();
  double precio = 5.0;

  Widget test = new MediaQuery(
      data: new MediaQueryData(),
      child: new MaterialApp(home: new PagoPayPalInt(precio, paypal))
  );

  group('Comprobar widget pago Paypal', () {
    testWidgets('Comprobar text en pago Paypal', (WidgetTester tester) async {
      // Primero vamos a comprobar que todos los campos de texto que hemos
      // colocado sean los correctos
      await tester.pumpWidget(test);

      // Título
      final text = find.text('PayPal');
      expect(text, findsOneWidget);

      // Primer textfield
      final text2 = find.text('Nombre de usuario');
      final text3 = find.text('Escribe su nome de usuario de PayPal...');
      expect(text2, findsOneWidget);
      expect(text3, findsOneWidget);

      // Segundo texfield
      final text4 = find.text('Correo Electrónico');
      final text5 = find.text('Escriba su correo electrónico...');
      expect(text4, findsOneWidget);
      expect(text5, findsOneWidget);

      // Text en el botón
      final text6 = find.text('Efectuar pago');
      expect(text6, findsOneWidget);
    });

    testWidgets('Comprobar textfield de pago Paypal', (WidgetTester tester) async {
      // A continuación vamos a comprobar que se puede escribir y almacenar los
      // valores en lso texfield de paypals
      await tester.pumpWidget(test);

      final testKey1 = Key('usuario');
      final testKey2 = Key('correo');

      await tester.enterText(find.byKey(testKey1), 'raulrguez');
      await tester.enterText(find.byKey(testKey2), 'raulrguez@correo.ugr');

      await tester.tap(find.byType(RaisedButton));
      await tester.pump();

      expect(find.text('raulrguez'), findsOneWidget);
      expect(find.text('raulrguez@correo.ugr'), findsOneWidget);
    });

  });
}
