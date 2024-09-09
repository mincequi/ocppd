import 'package:get/get.dart';
import 'package:webapp/models/ocpp_configuration_key.dart';

import 'ocpp_charge_point_status.dart';
import 'property_key.dart';

class ChargePoint {
  final String id;
  var properties = <PropertyKey, dynamic>{};
  var configuration = <OcppConfigurationKey, String>{}.obs;

  String get name => properties[PropertyKey.name] ?? id;
  OcppChargePointStatus? get status =>
      OcppChargePointStatus.values[properties[PropertyKey.status]];

  ChargePoint({required this.id, Map<PropertyKey, dynamic>? properties}) {
    if (properties != null) {
      updateProperties(properties);
    }
  }

  void updateProperties(Map<PropertyKey, dynamic> newProperties) {
    // do not replace all properties, only update the ones that are different
    newProperties.forEach((key, value) {
      if (properties[key] != value) {
        properties[key] = value;
      }
    });
  }
}
