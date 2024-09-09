// ConfigurationController to manage the state of configurations
import 'package:get/get.dart';

import '../models/configuration.dart';

class ConfigurationController extends GetxController {
  var configurations = <Configuration>[].obs;

  // Initialize with some default configurations
  @override
  void onInit() {
    super.onInit();
    configurations.value = [
      Configuration(key: 'API Endpoint', value: 'https://api.example.com'),
      Configuration(key: 'Timeout', value: '30'),
      Configuration(key: 'Theme', value: 'Light'),
      // Add more configurations as needed
    ];
  }

  // Update configuration value
  void updateConfiguration(String key, String newValue) {
    int index = configurations.indexWhere((config) => config.key == key);
    if (index != -1) {
      configurations[index] = Configuration(key: key, value: newValue);
      configurations.refresh();
    }
  }
}
