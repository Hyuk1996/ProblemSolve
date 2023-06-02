fun main() {
    // input && solution
    var tc = readln().toInt()
    val answers = mutableListOf<Pair<Int, Int>>()

    while (tc-- > 0) {
        val n = readln().toInt()
        val arr = readln().split(" ").map { it.toInt() }.toTypedArray()
        answers.add(Pair(arr.minOrNull()!!, arr.maxOrNull()!!))
    }

    // output
    for (answer in answers) {
        println("${answer.first} ${answer.second}")
    }
}
