import kotlin.math.abs

fun main() {
    // input
    val N = readln().toInt()
    val arr = readln().split(" ").map { it.toInt() }.toTypedArray()

    // solution
    var answer = 2000000001
    var value1 = 0
    var value2 = 0

    var left = 0
    var right = N - 1
    while (left < right) {
        val sum = arr[left] + arr[right]
        if (abs(sum) <= abs(answer)) {
            answer = sum
            value1 = arr[left]
            value2 = arr[right]
        }

        if (sum >= 0) {
            right--
        } else {
            left++
        }
    }

    // output
    println("$value1 $value2")
}
