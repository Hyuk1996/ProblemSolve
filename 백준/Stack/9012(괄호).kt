fun main() {
    // input
    var T = readln().toInt()
    val texts = Array(T) { "" }
    for (i in 0 until T) {
        texts[i] = readln()
    }

    // solution
    val answers = Array<String>(T) { "" }
    for (i in 0 until T) {
        val text = texts[i]

        val stack = ArrayDeque<Char>()
        var isVPS = true
        for (j in text.indices) {
            if (text[j] == '(') {
                stack.addLast(text[j])
            } else {
                if (stack.isEmpty()) {
                    isVPS = false
                } else {
                    stack.removeLast()
                }
            }
        }

        if (stack.isNotEmpty()) {
            isVPS = false
        }

        if (isVPS) answers[i] = "YES" else answers[i] = "NO"
    }

    // output
    for (answer in answers) {
        println(answer)
    }
}
