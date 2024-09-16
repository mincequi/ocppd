// A reactive widget for grouped settings (a group of switches)
import 'package:flutter/material.dart';
import 'package:get/get.dart';
import 'package:webapp/models/ocpp_configuration_key.dart';
import 'package:webapp/models/ocpp_measurand.dart';

import '../controllers/configuration_controller.dart';

class GroupedSettingSwitch extends StatelessWidget {
  final OcppConfigurationKey groupKey;
  final Map<String, bool> groupedSettings = OcppMeasurand.values
      .asMap()
      .map((index, value) => MapEntry(value.name, true));

  GroupedSettingSwitch({
    Key? key,
    required this.groupKey,
  }) : super(key: key);

  @override
  Widget build(BuildContext context) {
    final controller = Get.find<ConfigurationController>();

    return ListTile(
      dense: true,
      title: Text(groupKey.name),
      subtitle: Wrap(
        spacing: 4.0,
        runSpacing: 4.0,
        children: groupedSettings.keys.map((subSettingKey) {
          return FilterChip(
            showCheckmark: true,
            padding: EdgeInsets.zero, // Remove all padding around the label
            labelPadding: EdgeInsets.symmetric(
                horizontal: 4, vertical: -4), // Minimal padding insi
            label: Text(
              subSettingKey,
              style: TextStyle(fontSize: 10),
            ),
            selected: groupedSettings[subSettingKey]!,
            onSelected: (isSelected) {
              groupedSettings[subSettingKey] = isSelected;
              //controller.updateGroupedSetting(groupKey, subSettingKey, isSelected);
            },
            visualDensity: VisualDensity.compact,
          );
        }).toList(),
      ),
    );

    /*
    return Column(
      crossAxisAlignment: CrossAxisAlignment.start,
      children: [
        Text(groupKey.name,
            style: TextField()
                .decoration
                ?.labelStyle
                ?.copyWith(fontWeight: FontWeight.w100)),
        SizedBox(height: 10),
        Wrap(
          //mainAxisAlignment: MainAxisAlignment.spaceBetween,
          children: groupedSettings.keys.map((subSettingKey) {
            return FilterChip(
              label: Text(subSettingKey),
              selected: groupedSettings[subSettingKey]!,
              onSelected: (isSelected) {
                groupedSettings[subSettingKey] = isSelected;
                //controller.updateGroupedSetting(groupKey, subSettingKey, isSelected);
              },
            );
          }).toList(),
        ),
        Divider(),
      ],
    );*/
  }
}
