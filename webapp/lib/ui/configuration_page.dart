import 'package:flutter/material.dart';
import 'package:get/get.dart';
import 'package:webapp/controllers/charge_points_controller.dart';

import '../controllers/configurations_controller.dart';
import 'configuration_item.dart';

class ConfigurationPage extends StatelessWidget {
  final ConfigurationsController _configurationController =
      Get.put(ConfigurationsController());
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
              _configurationController.selectConfiguration(value);
              //_chargePointsController.selectedChargePoint.value = value;
            },
            dropdownMenuEntries: _chargePointsController.chargePoints
                .map((e) => DropdownMenuEntry<String>(
                    value: e.value.id, label: e.value.name))
                .toList(),
          ),
          const SizedBox(height: 4),
          Expanded(
              child: ListView.separated(
            separatorBuilder: (context, index) => const Padding(
                padding: EdgeInsets.symmetric(horizontal: 16),
                child: Divider(height: 4)),
            itemCount:
                _configurationController.selectedConfiguration.value != null
                    ? _configurationController
                        .selectedConfiguration.value!.properties.length
                    : 0,
            itemBuilder: (context, index) {
              final entry = _configurationController
                  .selectedConfiguration.value!.properties.entries
                  .elementAt(index);
              return ConfigurationItem(
                id: _configurationController.selectedConfiguration.value!.id,
                configKey: entry.key,
                configValue: entry.value,
              );
            },
          )),
        ],
      ),
    );
    //);
  }
}
