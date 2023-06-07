fun main() {
    // input
    val (n, m) = readln().split(" ").map { it.toInt() }

    // solution
    val combi = Array(100 + 1) { Array(100 + 1) { "" } }
    combi[0][0] = "1"
    for (i in 1..n) {
        for (j in 0..i) {
            if (j == 0 || j == i) {
                combi[i][j] = "1"
                continue
            }

            if (combi[i - 1][j - 1].length > combi[i - 1][j].length) {
                combi[i - 1][j] = combi[i - 1][j] + "0".repeat(combi[i - 1][j - 1].length - combi[i - 1][j].length)
            } else {
                combi[i - 1][j - 1] =
                    combi[i - 1][j - 1] + "0".repeat(combi[i - 1][j].length - combi[i - 1][j - 1].length)
            }

            val result = StringBuilder()
            var upCnt = false
            for (idx in combi[i - 1][j - 1].indices) {
                var sum = 0
                if(upCnt) {
                    sum++
                    upCnt = false
                }

                sum += (combi[i - 1][j - 1][idx] - '0') + (combi[i - 1][j][idx] - '0')

                if (sum >= 10) {
                    sum -= 10
                    upCnt = true
                }

                result.append(('0' + sum))
            }
            if (upCnt) {
                result.append('1')
            }

            combi[i][j] = result.toString()
        }
    }

    // output
    val answer = combi[n][m].reversed()
    var startIdx = -1
    for (i in answer.indices) {
        if (answer[i] != '0') {
            startIdx = i
            break
        }
    }

    println(answer.substring(startIdx))
}
