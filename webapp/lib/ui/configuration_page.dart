import 'package:flutter/material.dart';
import 'package:flutter/rendering.dart';
import 'package:get/get.dart';
import 'package:webapp/controllers/charge_points_controller.dart';

import '../controllers/configuration_controller.dart';
import 'configuration_card.dart';
import 'configuration_group.dart';

class ConfigurationPage extends StatelessWidget {
  final ConfigurationController _configurationController =
      Get.put(ConfigurationController());
  final ChargePointsController _chargePointsController =
      Get.put(ChargePointsController());

  @override
  Widget build(BuildContext context) {
    return Obx(
      () => Column(
        children: [
          DropdownMenu<String>(
            expandedInsets: EdgeInsets.all(16),
            initialSelection: _chargePointsController.chargePoints.isNotEmpty
                ? _chargePointsController.chargePoints.first.value.id
                : null,
            onSelected: (value) {
              //_chargePointsController.selectedChargePoint.value = value;
            },
            dropdownMenuEntries: _chargePointsController.chargePoints
                .map((e) => DropdownMenuEntry<String>(
                    value: e.value.id, label: e.value.name))
                .toList(),
          ),
          SizedBox(height: 4),
          Expanded(
              child: ListView.separated(
            separatorBuilder: (context, index) => Padding(
                padding: EdgeInsets.symmetric(horizontal: 16),
                child: Divider(height: 4)),
            itemCount: _configurationController.configurations.length,
            itemBuilder: (context, index) {
              final entry = _configurationController.configurations.entries
                  .elementAt(index);
              if (entry.value.value is List) {
                return GroupedSettingSwitch(
                  groupKey: entry.key,
                );
              } else if (entry.value.value is bool) {
                return SwitchListTile(
                    dense: true,
                    value: false,
                    onChanged: (newValue) {
                      //_controller.updateConfiguration(entry.key, newValue);
                    },
                    title: Text(entry.key.name));
              } else if (entry.value.value is int) {
                return ListTile(
                  dense: true,
                  title: Text(entry.key.name),
                  subtitle: Slider(
                    max: 100,
                    value: 5,
                    onChanged: (newValue) {
                      //_controller.updateConfiguration(entry.key, newValue);
                    },
                  ),
                );
              } else {
                return Padding(
                  padding: const EdgeInsets.only(bottom: 8.0),
                  child: TextFormField(
                    initialValue: entry.value.value.toString(),
                    decoration: InputDecoration(
                      labelText: entry.key.name,
                      //border: UnderlineInputBorder(),
                      //isDense: true, // Compact the field
                      //contentPadding: EdgeInsets.symmetric(vertical: 8),
                    ),
                    //onChanged: (newValue) {
                    //  _controller.updateConfiguration(entry.key, newValue);
                    //},
                  ),
                );
              }
            },
          )),
        ],
      ),
    );
    //);
  }
}
