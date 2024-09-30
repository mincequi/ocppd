import 'package:flutter/material.dart';
import 'package:get/get_rx/get_rx.dart';

import '../models/ocpp_configuration_key.dart';
import 'configuration_filter_chips.dart';

class ConfigurationItem extends StatelessWidget {
  final String id;
  final OcppConfigurationKey configKey;
  Rx<dynamic> configValue;

  ConfigurationItem({
    super.key,
    required this.id,
    required this.configKey,
    required this.configValue,
  });

  @override
  Widget build(BuildContext context) {
    if (configValue.value is List) {
      return ConfigurationFilterChips(
        id: id,
        groupKey: configKey,
        selectedMeasurands: configValue.value.cast<int>().toSet(),
      );
    } else if (configValue.value is bool) {
      return SwitchListTile(
          title: Text(configKey.name),
          dense: true,
          value: false,
          onChanged: (newValue) {
            //_controller.updateConfiguration(entry.key, newValue);
          });
    } else if (configValue.value is int) {
      return ListTile(
        title: Text(configKey.name),
        dense: true,
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
          initialValue: configValue.value.toString(),
          decoration: InputDecoration(
            labelText: configKey.name,
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
  }
}
