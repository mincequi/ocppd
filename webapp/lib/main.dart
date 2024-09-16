import 'package:flutter/material.dart';
import 'package:get/get.dart';
import 'package:webapp/controllers/configuration_controller.dart';
import 'package:webapp/ui/colors.dart';
import 'package:webapp/ui/main_page.dart';

import 'controllers/charge_points_controller.dart';
import 'services/web_socket_service.dart';
import 'ui/charge_points_page.dart';

void main() {
  // Initialize controllers and services
  Get.put(ChargePointsController(), permanent: true);
  Get.put(ConfigurationController(), permanent: true);
  Get.put(WebSocketService(), permanent: true);

  runApp(const MyApp());
}

class MyApp extends StatelessWidget {
  const MyApp({super.key});

  // This widget is the root of your application.
  @override
  Widget build(BuildContext context) {
    return GetMaterialApp(
      title: 'Ohssippippi',
      themeMode: ThemeMode.dark,
      darkTheme: ThemeData.dark(
        useMaterial3: true,
      ).copyWith(
        colorScheme: ColorScheme.fromSeed(
            seedColor: Palette.blue, brightness: Brightness.dark),
        cardTheme: CardTheme(
          shape: RoundedRectangleBorder(
            side: BorderSide(color: Palette.blue.withAlpha(127), width: 0),
            borderRadius: BorderRadius.circular(4),
          ),
        ),
      ),
      theme: ThemeData(
        // This is the theme of your application.
        //
        // TRY THIS: Try running your application with "flutter run". You'll see
        // the application has a purple toolbar. Then, without quitting the app,
        // try changing the seedColor in the colorScheme below to Colors.green
        // and then invoke "hot reload" (save your changes or press the "hot
        // reload" button in a Flutter-supported IDE, or press "r" if you used
        // the command line to start the app).
        //
        // Notice that the counter didn't reset back to zero; the application
        // state is not lost during the reload. To reset the state, use hot
        // restart instead.
        //
        // This works for code too, not just values: Most code changes can be
        // tested with just a hot reload.
        colorScheme: ColorScheme.fromSeed(seedColor: Palette.green),
        useMaterial3: true,
      ),
      //home: ChargePointsPage(),
      home: MainPage(),
    );
  }
}
