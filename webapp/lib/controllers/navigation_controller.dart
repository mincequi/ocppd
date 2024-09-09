// Controller to handle bottom navigation state
import 'package:flutter/material.dart';
import 'package:get/get.dart';
import '../models/ocpp_action.dart';
import '../services/web_socket_service.dart';
import '../ui/configuration_page.dart';
import '../ui/charge_points_page_new.dart';

class NavigationController extends GetxController {
  var webSocketService = Get.find<WebSocketService>();

  // Current selected index for bottom navigation
  var selectedIndex = 0.obs;

  // List of pages for each tab
  final List<Widget> pages = [
    ChargePointsPageNew(),
    ConfigurationPage(),
  ];

  // Method to change the selected index
  void changePage(int index) {
    selectedIndex.value = index;
  }

  bool isFabVisible() {
    return selectedIndex.value == 0;
  }

  // Change the FAB icon based on the selected page
  IconData fabIcon() {
    if (selectedIndex.value == 0) {
      return Icons.refresh; // Home Page FAB icon
    } else {
      return Icons.person; // Third Page FAB icon
    }
  }

  // Define different actions for the Floating Action Button based on the current tab
  void onFabPressed() {
    if (selectedIndex.value == 0) {
      webSocketService.sendAction(OcppAction.TriggerMessage);
    } else if (selectedIndex.value == 1) {
      Get.snackbar("Second Page", "FAB clicked on Second Page!");
    } else if (selectedIndex.value == 2) {
      Get.snackbar("Third Page", "FAB clicked on Third Page!");
    }
  }
}
