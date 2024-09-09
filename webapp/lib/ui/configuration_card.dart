// Widget for each configuration item with a label and editable text field
import 'package:flutter/material.dart';

import '../models/configuration.dart';

class ConfigurationCard extends StatelessWidget {
  final Configuration config;
  final ValueChanged<String> onChanged;

  ConfigurationCard({required this.config, required this.onChanged});

  @override
  Widget build(BuildContext context) {
    return Padding(
      padding: const EdgeInsets.all(8.0),
      child: Card(
        child: ListTile(
          title: Text(config.key),
          subtitle: TextField(
            controller: TextEditingController(text: config.value),
            decoration: InputDecoration(labelText: 'Value'),
            onChanged: onChanged,
          ),
        ),
      ),
    );
  }
}
