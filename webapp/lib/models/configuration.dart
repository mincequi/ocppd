// Configuration model
import 'package:get/get_rx/get_rx.dart';
import 'package:webapp/models/ocpp_configuration_key.dart';

class Configuration {
  final String id;
  var properties = <OcppConfigurationKey, Rx<dynamic>>{};

  Configuration(
      {required this.id, Map<OcppConfigurationKey, dynamic>? properties}) {
    if (properties != null) {
      updateProperties(properties);
    }
  }

  void updateProperties(Map<OcppConfigurationKey, dynamic> newProperties) {
    newProperties.forEach((key, value) {
      if (properties.containsKey(key)) {
        properties[key]!.value = value;
      } else {
        properties[key] = Rx<dynamic>(value);
      }
    });
  }
}
