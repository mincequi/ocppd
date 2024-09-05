import 'package:flutter/material.dart';
import 'package:get/get.dart';
import 'package:webapp/models/property_key.dart';

import '../controllers/charge_points_controller.dart';
import '../models/charge_point.dart';
import '../services/web_socket_service.dart';

class ChargePointCard extends StatelessWidget {
  final Rx<ChargePoint> chargePoint;

  ChargePointCard({required this.chargePoint});

  var _editedName = '';
  final _webSocketService = Get.find<WebSocketService>();

  @override
  Widget build(BuildContext context) {
    return Card(
      child: Obx(() {
        return Column(
          crossAxisAlignment: CrossAxisAlignment.start,
          children: [
            ListTile(
              leading: Icon(Icons.ev_station, size: 40),
              title: Text('${chargePoint.value.name}',
                  style: TextStyle(fontSize: 18, fontWeight: FontWeight.bold)),

              // Show status as subtitle
              subtitle: Text(
                  '${chargePoint.value.status.toString().split('.').last}',
                  style: TextStyle(fontSize: 16)),

              //subtitle: Text('ID: ${chargePoint.value.id}',
              //    style: TextStyle(fontSize: 16)),
              // Rename charge point and only apply on save
              trailing: IconButton(
                icon: Icon(Icons.edit),
                onPressed: () {
                  Get.defaultDialog(
                    // Hide title
                    titleStyle: TextStyle(fontSize: 0),
                    content: TextField(
                      autofocus: true,
                      controller:
                          TextEditingController(text: chargePoint.value.name),
                      onChanged: (value) {
                        _editedName = value;
                      },
                    ),
                    actions: [
                      TextButton(
                        onPressed: () {
                          Get.back();
                        },
                        child: Icon(Icons.close),
                      ),
                      TextButton(
                        onPressed: () {
                          _webSocketService.sendMessage(chargePoint.value.id,
                              PropertyKey.name, _editedName);
                          Get.back();
                        },
                        child: Icon(Icons.save),
                      ),
                    ],
                  );
                },
              ),
            ),
            Text('Power: ${chargePoint.value.properties[PropertyKey.power]} kW',
                style: TextStyle(fontSize: 16)),
          ],
        );
      }),
    );
  }
}
