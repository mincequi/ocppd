// A reactive widget for grouped settings (a group of switches)
import 'package:flutter/material.dart';
import 'package:get/get.dart';
import 'package:webapp/models/ocpp_configuration_key.dart';
import 'package:webapp/models/ocpp_measurand.dart';
import 'package:webapp/services/web_socket_service.dart';

class ConfigurationFilterChips extends StatelessWidget {
  final String id;
  final OcppConfigurationKey groupKey;
  final Set<int> selectedMeasurands;
  final Map<OcppMeasurand, bool> groupedSettings = OcppMeasurand.values
      .asMap()
      .map((index, value) => MapEntry(value, false));

  WebSocketService _wsService = Get.find<WebSocketService>();

  ConfigurationFilterChips({
    Key? key,
    required this.id,
    required this.groupKey,
    required this.selectedMeasurands,
  }) : super(key: key) {
    for (var measurand in selectedMeasurands) {
      groupedSettings[OcppMeasurand.values[measurand]] = true;
    }
  }

  @override
  Widget build(BuildContext context) {
    return ListTile(
      dense: true,
      title: Text(groupKey.name),
      subtitle: Wrap(
        spacing: 4.0,
        runSpacing: 4.0,
        children: groupedSettings.keys.map((measurand) {
          return FilterChip(
            showCheckmark: true,
            padding: EdgeInsets.zero, // Remove all padding around the label
            labelPadding: const EdgeInsets.symmetric(
                horizontal: 4, vertical: -4), // Minimal padding insi
            label: Text(
              measurand.name,
              style: const TextStyle(fontSize: 10),
            ),
            selected: groupedSettings[measurand]!,
            onSelected: (isSelected) {
              groupedSettings[measurand] = isSelected;
              final measurands = groupedSettings.entries
                  .where((entry) => entry.value)
                  .map((entry) => entry.key.index)
                  .toList();

              _wsService.sendOcppConfiguration(id, groupKey, measurands);

              //controller.updateGroupedSetting(groupKey, subSettingKey, isSelected);
            },
            visualDensity: VisualDensity.compact,
          );
        }).toList(),
      ),
    );
  }

  dynamic _toValue(OcppConfigurationKey key, dynamic value) {
    switch (key) {
      case OcppConfigurationKey.MeterValuesSampledData:
      case OcppConfigurationKey.MeterValuesAlignedData:
        List<OcppMeasurand> measurands = (value as List).map((e) {
          return OcppMeasurand.values[e];
        }).toList();
        return measurands;
      default:
        return value;
    }
  }
}
