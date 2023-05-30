fun main() {
    // input && solution
    var T = readln().toInt()
    val answers = mutableListOf<Int>()
    while (T-- > 0) {
        val sb = StringBuilder()
        for (i in 0..2) {
            readln().split(" ").map { if (it == "H") sb.append("0") else sb.append("1") }
        }
        val start = sb.toString()

        val visited = BooleanArray(512 + 1) { false }
        val queue = ArrayDeque<String>()
        var cnt = 0
        var answer = -1

        queue.addLast(start)
        while (queue.isNotEmpty()) {
            var qSize = queue.size
            while (qSize-- > 0) {
                val last = queue.removeFirst()

                if (visited[last.toInt(2)]) {
                    continue
                }

                // validate game end
                if (last.toInt(2) == 0 || last.toInt(2) == 512 - 1) {
                    answer = cnt
                    queue.clear()
                    break
                }

                visited[last.toInt(2)] = true

                // change row
                for (i in 0..2) {
                    val sb = StringBuilder(last)
                    for (j in 0..2) {
                        if (sb[(3 * i) + j] == '0') {
                            sb[(3 * i) + j] = '1'
                        } else {
                            sb[(3 * i) + j] = '0'
                        }
                    }
                    if (!visited[sb.toString().toInt(2)]) {
                        queue.addLast(sb.toString())
                    }
                }

                // change column
                for (i in 0..2) {
                    val sb = StringBuilder(last)
                    for (j in 0..2) {
                        if (sb[(3 * j) + i] == '0') {
                            sb[(3 * j) + i] = '1'
                        } else {
                            sb[(3 * j) + i] = '0'
                        }
                    }
                    if (!visited[sb.toString().toInt(2)]) {
                        queue.addLast(sb.toString())
                    }
                }

                // change diagonal
                val sb = StringBuilder(last)
                if (sb[0] == '0') {
                    sb[0] = '1'
                } else {
                    sb[0] = '0'
                }

                if (sb[4] == '0') {
                    sb[4] = '1'
                } else {
                    sb[4] = '0'
                }

                if (sb[8] == '0') {
                    sb[8] = '1'
                } else {
                    sb[8] = '0'
                }

                if (!visited[sb.toString().toInt(2)]) {
                    queue.addLast(sb.toString())
                }

                sb.clear()
                sb.append(last)

                if (sb[2] == '0') {
                    sb[2] = '1'
                } else {
                    sb[2] = '0'
                }

                if (sb[4] == '0') {
                    sb[4] = '1'
                } else {
                    sb[4] = '0'
                }

                if (sb[6] == '0') {
                    sb[6] = '1'
                } else {
                    sb[6] = '0'
                }

                if (!visited[sb.toString().toInt(2)]) {
                    queue.addLast(sb.toString())
                }
            }
            cnt++
        }
        answers.add(answer)
    }

    // output
    for (answer in answers) {
        println(answer)
    }
}

