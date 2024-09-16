// ConfigurationController to manage the state of configurations
import 'package:get/get.dart';
import 'package:webapp/models/ocpp_measurand.dart';

import '../models/configuration.dart';
import '../models/ocpp_configuration_key.dart';

class ConfigurationController extends GetxController {
  var configurations = <OcppConfigurationKey, Rx<dynamic>>{}.obs;

  void updateConfiguration(Map<OcppConfigurationKey, dynamic> newConfigs) {
    newConfigs.forEach((key, value) {
      if (configurations.containsKey(key)) {
        configurations[key]!.value = toValue(key, value);
      } else {
        configurations[key] = Rx<dynamic>(toValue(key, value));
      }
    });
  }

  dynamic toValue(OcppConfigurationKey key, dynamic value) {
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
