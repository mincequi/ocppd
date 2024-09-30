import 'package:flutter/material.dart';
import 'package:geekyants_flutter_gauges/geekyants_flutter_gauges.dart';
import 'package:get/get.dart';
import 'package:webapp/models/property_key.dart';
import 'package:webapp/ui/colors.dart';

import '../models/charge_point.dart';
import '../services/web_socket_service.dart';

class ChargePointCard extends StatelessWidget {
  final _webSocketService = Get.find<WebSocketService>();

  final Rx<ChargePoint> chargePoint;
  String _editedName;

  final RxnInt _powerOffered = RxnInt(null);

  ChargePointCard({required this.chargePoint})
      : _editedName = chargePoint.value.name {
    _powerOffered.listen((value) {
      if (value != null) {
        _webSocketService.sendMessage(
            chargePoint.value.id, PropertyKey.powerOffered, value * 100);
      }
    });
  }

  @override
  Widget build(BuildContext context) {
    return Card(
      child: Obx(() {
        return Column(
          crossAxisAlignment: CrossAxisAlignment.start,
          children: [
            Stack(
              children: [
                // Show status as background color
                // Show status as text
                ListTile(
                  leading: Icon(Icons.ev_station, size: 40),
                  title: Text('${chargePoint.value.name}',
                      style:
                          TextStyle(fontSize: 18, fontWeight: FontWeight.bold)),

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
                          controller: TextEditingController(
                              text: chargePoint.value.name),
                          onChanged: (value) {
                            _editedName = value;
                          },
                          // handle enter key
                          onSubmitted: (value) {
                            _webSocketService.sendMessage(chargePoint.value.id,
                                PropertyKey.name, _editedName);
                            Get.back();
                          },
                        ),
                        actions: [
                          // Restore button
                          TextButton(
                            onPressed: () {
                              _editedName = chargePoint.value.id;
                              _webSocketService.sendMessage(
                                  chargePoint.value.id,
                                  PropertyKey.name,
                                  _editedName);
                              Get.back();
                            },
                            // Add reset icon
                            child: const Icon(Icons.restore),
                          ),
                          // Close button
                          TextButton(
                            onPressed: () {
                              Get.back();
                            },
                            child: const Icon(Icons.close),
                          ),
                          // Save button
                          TextButton(
                            onPressed: () {
                              _webSocketService.sendMessage(
                                  chargePoint.value.id,
                                  PropertyKey.name,
                                  _editedName);
                              Get.back();
                            },
                            child: const Icon(Icons.save),
                          ),
                        ],
                      );
                    },
                  ),
                ),
              ],
            ),
            Padding(
              padding: EdgeInsets.only(left: 9, right: 34, top: 8, bottom: 12),
              child: LinearGauge(
                linearGaugeBoxDecoration: LinearGaugeBoxDecoration(
                  backgroundColor: Theme.of(context).scaffoldBackgroundColor,
                  thickness: 8,
                  borderRadius: 2,
                ),
                customLabels: [
                  CustomRulerLabel(text: "0 kW", value: 0),
                  CustomRulerLabel(text: "3.7 kW", value: 3.7),
                  CustomRulerLabel(text: "11 kW", value: 11),
                  CustomRulerLabel(text: "", value: 12),
                ],
                enableGaugeAnimation: true,
                valueBar: [
                  ValueBar(
                      color: Palette.red,
                      valueBarThickness: 8,
                      borderRadius: 2,
                      value: chargePoint.value.properties[PropertyKey.power] /
                              1000 ??
                          0)
                ],
                start: 0,
                end: 12,
                rulers: RulerStyle(
                  rulerPosition: RulerPosition.bottom,
                  showPrimaryRulers: false,
                  showSecondaryRulers: false,
                ),
                pointers: [
                  Pointer(
                    color: Palette.blue,
                    shape: PointerShape.triangle,
                    width: 20,
                    height: 20,
                    pointerPosition: PointerPosition.top,
                    value:
                        chargePoint.value.properties[PropertyKey.powerOffered] /
                                1000 ??
                            0,
                    isInteractive: true,
                    onChanged: (newValue) {
                      _powerOffered.value = (newValue * 10).round();
                    },
                    //value: chargePoint.value.properties[PropertyKey.power],
                  ),
                ],
              ),
            ),
            //Text('Power: ${chargePoint.value.properties[PropertyKey.power]/1000} kW',
            //    style: TextStyle(fontSize: 16)),
          ],
        );
      }),
    );
  }
}
