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
  PagoPaypal paypal = new PagoPaypal();
  PagoTransferencia trans = new PagoTransferencia();
  double precio = 0.0;

  Widget test = new MediaQuery(
      data: new MediaQueryData(),
      child: new MaterialApp(home: new MySecondPage(target, alquileres, paypal, tarjeta, trans))
  );

  group('Comprobar objetivo', () {
    testWidgets('Comprobar text en objetivo', (WidgetTester tester) async {
      // Primero vamos a comprobar que todos los campos de texto que hemos
      // colocado sean los correctos
      await tester.pumpWidget(test);

      // Título
      final text = find.text('Meet & Match');
      expect(text, findsOneWidget);

      // Primer dropbutton
      final text2 = find.text('Elige un deporte');
      expect(text2, findsOneWidget);

      // Primer texfield
      final text3 = find.text('Ubicación');
      expect(text3, findsOneWidget);

      // Segundo texfield
      final text4 = find.text('Fecha');
      expect(text4, findsOneWidget);

      // Segundo dropbutton
      final text5 = find.text('Elige el tiempo en minutos');
      expect(text5, findsOneWidget);

      // Tercer texfield
      final text6 = find.text('Nº personas');
      expect(text6, findsOneWidget);

      // Tercer dropbutton
      final text7 = find.text('Elige el método de pago');
      expect(text7, findsOneWidget);

      // Text en el primer botón
      final text8 = find.text('Alquilar');
      expect(text8, findsOneWidget);

      // Text en el segundo botón
      final text9 = find.text('Ver Objetivo');
      expect(text9, findsOneWidget);
    });

    testWidgets('Comprobar textfield de objetivo', (WidgetTester tester) async {
      // A continuación vamos a comprobar que se puede escribir y almacenar los
      // valores en lso texfield de paypals
      await tester.pumpWidget(test);

      final testKey1 = Key('ubicacion');
      final testKey2 = Key('fecha_alquiler');
      final testKey3 = Key('npersonas');

      await tester.enterText(find.byKey(testKey1), 'Maracena');
      await tester.enterText(find.byKey(testKey2), '22/22/2222 12:12');
      await tester.enterText(find.byKey(testKey3), '5');

      await tester.tap(find.byKey(Key('Alquilar')));
      await tester.pump();

      expect(find.text('Maracena'), findsOneWidget);
      expect(find.text('22/22/2222 12:12'), findsOneWidget);
      expect(find.text('5'), findsOneWidget);
    });

  });
}
