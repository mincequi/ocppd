import 'package:flutter/material.dart';
import 'package:get/get.dart';

import '../controllers/charge_points_controller.dart';
import 'charge_point_card.dart';

class ChargePointsPage extends StatelessWidget {
  // Retrieve the controller using GetX dependency injection
  final ChargePointsController controller = Get.find<ChargePointsController>();

  @override
  Widget build(BuildContext context) {
    return Padding(
        padding: EdgeInsets.all(8),
        child: Obx(
          () => ListView.builder(
            itemCount: controller.chargePoints.length,
            itemBuilder: (context, index) {
              return ChargePointCard(
                  chargePoint: controller.chargePoints[index]);
            },
          ),
        ));
  }
}
