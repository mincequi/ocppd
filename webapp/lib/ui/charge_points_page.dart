import 'package:flutter/material.dart';
import 'package:get/get.dart';
import 'package:webapp/models/ocpp_action.dart';
import '../controllers/charge_points_controller.dart';
import '../services/web_socket_service.dart';
import 'charge_point_card.dart';

class ChargePointsPage extends StatelessWidget {
  // Retrieve the controller using GetX dependency injection
  final ChargePointsController controller = Get.find<ChargePointsController>();
  // Retrieve web socket service using GetX dependency injection
  final WebSocketService webSocketService = Get.find<WebSocketService>();

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      body: Padding(
          padding: EdgeInsets.all(8),
          child: Obx(
            () => ListView.builder(
              itemCount: controller.chargePoints.length,
              itemBuilder: (context, index) {
                return ChargePointCard(
                    chargePoint: controller.chargePoints[index]);
              },
            ),
          )),
      floatingActionButton: FloatingActionButton(
        shape: RoundedRectangleBorder(
          borderRadius: BorderRadius.circular(4),
        ),
        onPressed: () {
          webSocketService.sendAction(OcppAction.TriggerMessage);
        },
        // trigger message icon
        child: Icon(Icons.refresh),
      ),
    );
  }
}
