import 'package:web_socket_channel/web_socket_channel.dart';
import 'package:get/get.dart';
import 'package:cbor/simple.dart';
import 'package:webapp/models/property_key.dart';

import '../controllers/charge_points_controller.dart';

class WebSocketService {
  //final _host = html.window.location.hostname;
  //final _port = int.parse(html.window.location.port);
  final _host = "localhost";
  final _port = 8030;

  late final WebSocketChannel _channel;
  final ChargePointsController _chargePointsController =
      Get.find<ChargePointsController>();

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

    if (decodedData is Map) {
      decodedData.forEach((key, value) {
        Map<PropertyKey, dynamic> properties = {};
        value.forEach((k, v) {
          properties[PropertyKey.values[int.parse(k)]] = v;
        });
        _chargePointsController.updateChargePointProperties(key, properties);
      });
    }
  }

  void sendMessage(String id, PropertyKey key, dynamic value) {
    _channel.sink.add(cbor.encode({
      id: {key.index.toString(): value}
    }));
  }

  void close() {
    _channel.sink.close();
  }
}
