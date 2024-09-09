import 'package:flutter/material.dart';
import 'package:get/get.dart';

import '../controllers/navigation_controller.dart';

class MainPage extends StatelessWidget {
  final NavigationController navController = Get.put(NavigationController());

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text('OCPP Central'),
      ),
      // Body of the Scaffold shows the selected page
      body: Obx(() => navController.pages[navController.selectedIndex.value]),
      // Bottom Navigation Bar
      bottomNavigationBar: Obx(() => BottomNavigationBar(
            currentIndex: navController.selectedIndex.value,
            onTap: (index) => navController.changePage(index),
            items: [
              BottomNavigationBarItem(
                icon: Icon(Icons.ev_station),
                label: 'Charge Points',
              ),
              BottomNavigationBarItem(
                icon: Icon(Icons.settings),
                label: 'Configuration',
              ),
            ],
          )),
      // Conditionally display the FAB only on certain pages
      floatingActionButton: Obx(() => navController.isFabVisible()
          ? FloatingActionButton(
              shape: RoundedRectangleBorder(
                borderRadius: BorderRadius.circular(4),
              ),
              onPressed: () => navController.onFabPressed(),
              child: Icon(
                  navController.fabIcon()), // Icon depends on the current page
            )
          : Container()),
    );
  }
}
