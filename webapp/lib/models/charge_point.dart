import 'charge_point_status.dart';
import 'property_key.dart';

class ChargePoint {
  final String id;
  Map<PropertyKey, dynamic> properties = {};

  String get name => properties[PropertyKey.name] ?? id;
  ChargePointStatus? get status =>
      ChargePointStatus.values[properties[PropertyKey.status]];

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
