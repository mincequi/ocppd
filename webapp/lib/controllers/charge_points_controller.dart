import 'package:get/get.dart';
import '../models/charge_point.dart';
import '../models/property_key.dart';

class ChargePointsController extends GetxController {
  // Reactive list of Chargepoints
  RxList<Rx<ChargePoint>> chargePoints = <Rx<ChargePoint>>[].obs;

  @override
  void onInit() {
    super.onInit();
  }

  void updateChargePointProperties(
      String chargePointId, Map<PropertyKey, dynamic> newProperties) {
    final chargePoint = chargePoints
        .firstWhere((cp) => cp.value.id == chargePointId, orElse: () {
      var newCp = ChargePoint(
        id: chargePointId,
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
