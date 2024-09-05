import 'package:flutter/material.dart';
import 'package:get/get.dart';
import 'charge_point_card.dart';
import '../controllers/charge_points_controller.dart';
import '../models/charge_point.dart';

class ChargePointsPage extends StatelessWidget {
  // Retrieve the controller using GetX dependency injection
  final ChargePointsController controller = Get.put(ChargePointsController());

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text('Chargepoints List'),
      ),
      body: Obx(
        () => ListView.builder(
          itemCount: controller.chargePoints.length,
          itemBuilder: (context, index) {
            return ChargePointCard(chargePoint: controller.chargePoints[index]);
          },
        ),
      ),
      //floatingActionButton: FloatingActionButton(
      //  onPressed: () {
      //    // Use the controller to add a new chargepoint
      //    controller.addChargePoint();
      //  },
      //  child: Icon(Icons.add),
      //),
    );
  }
}
