fun main() {
    // input
    val N = readln().toInt()
    val nums = readln()

    // solution
    var sum = 0
    for (i in nums.indices) {
        sum += nums[i] - '0'
    }

    // output
    println(sum)
}
