// ConfigurationController to manage the state of configurations
import 'package:get/get.dart';
import 'package:webapp/models/ocpp_measurand.dart';

import '../models/configuration.dart';
import '../models/ocpp_configuration_key.dart';

class ConfigurationsController extends GetxController {
  var configurations = RxList<Configuration>();
  var selectedConfiguration = Rx<Configuration?>(null);

  void updateConfiguration(
      String id, Map<OcppConfigurationKey, dynamic> newConfigs) {
    final configuration =
        configurations.firstWhere((cp) => cp.id == id, orElse: () {
      var newConfig = Configuration(
        id: id,
      );
      configurations.add(newConfig);
      selectedConfiguration.value ??= newConfig;
      return newConfig;
    });
    configuration.updateProperties(newConfigs);
  }

  void removeConfiguration(String id) {
    configurations.removeWhere((conf) => conf.id == id);
  }

  void selectConfiguration(String? id) {
    selectedConfiguration.value =
        configurations.firstWhereOrNull((conf) => conf.id == id);
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
