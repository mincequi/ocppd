import 'package:get/get.dart';
import '../models/charge_point.dart';
import '../models/property_key.dart';

class ChargePointsController extends GetxController {
  // Reactive list of Chargepoints
  RxList<Rx<ChargePoint>> chargePoints = <Rx<ChargePoint>>[].obs;

  void updateChargePointProperties(
      String id, Map<PropertyKey, dynamic> newProperties) {
    final chargePoint =
        chargePoints.firstWhere((cp) => cp.value.id == id, orElse: () {
      var newCp = ChargePoint(
        id: id,
      ).obs;
      chargePoints.add(newCp);
      return newCp;
    });
    chargePoint.update((val) {
      val?.updateProperties(newProperties); // Update specific ChargePoint
    });
  }

  void removeChargePoint(String chargePointId) {
    chargePoints.removeWhere((cp) => cp.value.id == chargePointId);
  }
}
