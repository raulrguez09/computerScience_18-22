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
  PagoTarjeta tarjeta = new PagoTarjeta();
  PagoTransferencia trans = new PagoTransferencia();
  double precio = 5.0;

  Widget test = new MediaQuery(
      data: new MediaQueryData(),
      child: new MaterialApp(home: new PagoTarjetaInt(precio, tarjeta))
  );

  group('Comprobar método de pago tarjeta', () {
    testWidgets('Comprobar text en pago tarjeta', (WidgetTester tester) async {
      // Primero vamos a comprobar que todos los campos de texto que hemos
      // colocado sean los correctos
      await tester.pumpWidget(test);

      // Título
      final text = find.text('Tarjeta');
      expect(text, findsOneWidget);

      // Primer textfield
      final text2 = find.text('Número de la tarjeta');
      final text3 = find.text('Escribe el número de la tarjeta...');
      expect(text2, findsOneWidget);
      expect(text3, findsOneWidget);

      // Segundo texfield
      final text4 = find.text('Fecha caducidad');
      final text5 = find.text('Fecha estilo mm/yy...');
      expect(text4, findsOneWidget);
      expect(text5, findsOneWidget);

      // Segundo texfield
      final text6 = find.text('Número de seguridad');
      final text7 = find.text('Escriba el número de seguridad de su tarjeta...');
      expect(text4, findsOneWidget);
      expect(text5, findsOneWidget);

      // Text en el botón
      final text8 = find.text('Efectuar pago');
      expect(text6, findsOneWidget);
    });

    testWidgets('Comprobar textfield de pago Tarjeta', (WidgetTester tester) async {
      // A continuación vamos a comprobar que se puede escribir y almacenar los
      // valores en lso texfield de paypals
      await tester.pumpWidget(test);

      final testKey1 = Key('numero');
      final testKey2 = Key('fecha');
      final testKey3 = Key('seguridad');

      await tester.enterText(find.byKey(testKey1), '45678912312');
      await tester.enterText(find.byKey(testKey2), '22/22');
      await tester.enterText(find.byKey(testKey3), '619');

      await tester.tap(find.byType(RaisedButton));
      await tester.pump();

      expect(find.text('45678912312'), findsOneWidget);
      expect(find.text('22/22'), findsOneWidget);
      expect(find.text('619'), findsOneWidget);
    });

  });
}
