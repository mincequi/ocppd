import 'package:flutter/material.dart';
import 'package:get/get.dart';

import '../controllers/configuration_controller.dart';
import 'configuration_card.dart';

class ConfigurationPage extends StatelessWidget {
  final ConfigurationController _controller =
      Get.put(ConfigurationController());

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text('Configuration Options'),
      ),
      body: Obx(
        () => ListView.builder(
          itemCount: _controller.configurations.length,
          itemBuilder: (context, index) {
            final config = _controller.configurations[index];
            return ConfigurationCard(
              config: config,
              onChanged: (newValue) {
                _controller.updateConfiguration(config.key, newValue);
              },
            );
          },
        ),
      ),
    );
  }
}
