import 'dart:convert';

import 'package:web_socket_channel/web_socket_channel.dart';
import 'package:get/get.dart';
import 'package:cbor/simple.dart';
import 'package:webapp/models/ocpp_action.dart';
import 'package:webapp/models/ocpp_configuration_key.dart';
import 'package:webapp/models/property_key.dart';

import '../controllers/charge_points_controller.dart';
import '../controllers/configurations_controller.dart';
import '../models/ocpp_measurand.dart';

class WebSocketService {
  //final _host = html.window.location.hostname;
  //final _port = int.parse(html.window.location.port);
  final _host = "localhost";
  final _port = 8030;

  late final WebSocketChannel _channel;
  final ChargePointsController _chargePointsController = Get.find();
  final ConfigurationsController _configController = Get.find();

  WebSocketService() {
    _connect();
  }

  void _connect() {
    _channel = WebSocketChannel.connect(Uri.parse('ws://$_host:$_port/api'));

    _channel.stream.listen(
      (data) {
        _onMessage(data);
      },
    );
  }

  void _onMessage(dynamic data) {
    final decodedData = cbor.decode(data);
    if (decodedData is! Map) {
      return;
    }

    for (var kv in decodedData.entries) {
      final id = kv.key;
      if (kv.value is! Map) {
        continue;
      }

      var map = kv.value as Map;
      if (map.isEmpty) {
        _chargePointsController.removeChargePoint(id);
        _configController.removeConfiguration(id);
        continue;
      }

      var properties = map["properties"] ?? {};
      Map<PropertyKey, dynamic> newProperties = {};
      properties.forEach((k, v) {
        newProperties[PropertyKey.values[int.parse(k)]] = v;
      });
      _chargePointsController.updateChargePointProperties(id, newProperties);

      var configuration = map["configuration"] ?? {};
      Map<OcppConfigurationKey, dynamic> newConfiguration = {};
      configuration.forEach((k, v) {
        newConfiguration[OcppConfigurationKey.values[int.parse(k)]] = v;
      });
      _configController.updateConfiguration(id, newConfiguration);
    }
  }

  void sendMessage(String id, PropertyKey key, dynamic value) {
    _channel.sink.add(cbor.encode({
      id: {key.index.toString(): value}
    }));
  }

  void sendOcppConfiguration(
      String id, OcppConfigurationKey groupKey, List<int> selectedMeasurands) {
    _channel.sink.add(cbor.encode({
      id: {
        "configuration": {groupKey.index.toString(): selectedMeasurands}
      }
    }));
  }

  void sendAction(OcppAction action,
      {String? chargePointId, String? key, String? value}) {
    _channel.sink.add(json.encode([action.name, chargePointId, key, value]));
  }

  void close() {
    _channel.sink.close();
  }
}
