fun main() {
    // input
    val N = readln().toInt()
    val stuffs = readln().split(" ").map { it.toInt() }.toTypedArray()

    // solution
    stuffs.sort()
    var lo = 0
    var hi = N - 1
    var totalPrice = 0
    while (lo <= hi) {
        if (lo == hi) {
            totalPrice += stuffs[lo]
        } else {
            totalPrice += (stuffs[hi] * 2)
        }
        ++lo
        --hi
    }

    // output
    println(totalPrice)
}
