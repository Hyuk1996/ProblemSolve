class Solution {
    fun solution(cap: Int, n: Int, deliveries: IntArray, pickups: IntArray): Long {

        val deliveriesInfo = ArrayDeque<Info>()
        deliveries.forEachIndexed { index, deliveryCnt ->
            if (deliveryCnt > 0) {
                deliveriesInfo.addLast(Info(index + 1, deliveryCnt))
            }
        }

        val pickupsInfo = ArrayDeque<Info>()
        pickups.forEachIndexed { index, pickupCnt ->
            if (pickupCnt > 0) {
                pickupsInfo.addLast(Info(index + 1, pickupCnt))
            }
        }

        var answer: Long = 0L
        while (deliveriesInfo.isNotEmpty() || pickupsInfo.isNotEmpty()) {
            var furthestHouseNo = 0
            if (deliveriesInfo.isNotEmpty()) {
                if (deliveriesInfo.last().houseNo > furthestHouseNo) {
                    furthestHouseNo = deliveriesInfo.last().houseNo
                }
            }

            if (pickupsInfo.isNotEmpty()) {
                if (pickupsInfo.last().houseNo > furthestHouseNo) {
                    furthestHouseNo = pickupsInfo.last().houseNo
                }
            }

            answer += (2 * furthestHouseNo)

            var curDeliveryCnt = 0
            while (deliveriesInfo.isNotEmpty()) {
                val info = deliveriesInfo.removeLast()
                if (info.cnt > cap - curDeliveryCnt) {
                    deliveriesInfo.addLast(Info(info.houseNo, info.cnt - (cap - curDeliveryCnt)))
                    break;
                }

                curDeliveryCnt += info.cnt
            }

            var curPickupCnt = 0
            while (pickupsInfo.isNotEmpty()) {
                val info = pickupsInfo.removeLast()
                if (info.cnt > cap - curPickupCnt) {
                    pickupsInfo.addLast(Info(info.houseNo, info.cnt - (cap - curPickupCnt)))
                    break
                }

                curPickupCnt += info.cnt
            }
        }
        return answer
    }

    data class Info(val houseNo: Int, val cnt: Int)
}
