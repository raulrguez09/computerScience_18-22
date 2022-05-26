import 'package:ejemplods/Alquileres.dart';
import 'package:ejemplods/Objetivo.dart';
import 'package:ejemplods/PagoPaypal.dart';
import 'package:ejemplods/PagoTarjeta.dart';
import 'package:ejemplods/PagoTransferencia.dart';
import 'package:ejemplods/main.dart';
import 'package:flutter/material.dart';
import 'package:flutter_test/flutter_test.dart';
import 'package:integration_test/integration_test.dart';
import 'package:ejemplods/main.dart' as app;

void main() {
  Objetivo target = new Objetivo();
  Alquileres alquileres = new Alquileres();
  PagoTarjeta tarjeta = new PagoTarjeta();
  PagoPaypal paypal = new PagoPaypal();
  PagoTransferencia trans = new PagoTransferencia();
  double precio = 5.0;

  Widget test = new MediaQuery(
      data: new MediaQueryData(),
      child: new MaterialApp(home: new app.HomePage(target, alquileres, paypal, tarjeta, trans))
  );

  Widget test2 = new MediaQuery(
      data: new MediaQueryData(),
      child: new MaterialApp(home: new MySecondPage(target, alquileres, paypal, tarjeta, trans))
  );

  group('App Test', () {
    IntegrationTestWidgetsFlutterBinding.ensureInitialized();
    testWidgets('Ejemplo integración', (WidgetTester tester) async {
      await tester.pumpWidget(test);
      await tester.tap(find.byType(RaisedButton));
      await tester.pump();

      await tester.pumpWidget(test2);
      final testKey1 = Key('ubicacion');
      final testKey2 = Key('fecha_alquiler');
      final testKey3 = Key('npersonas');

      await tester.enterText(find.byKey(testKey1), 'Maracena');
      await tester.enterText(find.byKey(testKey2), '22/22/2222 12:12');
      await tester.enterText(find.byKey(testKey3), '5');

      await tester.tap(find.byKey(Key('Alquilar')));
      await tester.pump();
    });
  });
}