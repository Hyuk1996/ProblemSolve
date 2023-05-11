import java.util.*

// Solution 1 : Implementation
fun main() {
    // input
    val scanner = Scanner(System.`in`)

    val N = scanner.nextInt()
    val cycle = IntArray(size = N + 1)
    val visited = BooleanArray(size = N + 1) { false }

    for (i in 1..N) {
        val num = scanner.nextInt()
        cycle[i] = num
    }

    // solution
    val answer = mutableListOf<Int>()

    var idx = 1
    while (answer.size < N - 1) {
        answer.add(idx)
        visited[idx] = true
        var moveCnt = cycle[idx]

        if (moveCnt >= 0) {
            while (moveCnt > 0) {
                if (idx == N) {
                    idx = 1
                } else {
                    idx++
                }

                if (!visited[idx]) {
                    moveCnt--
                }
            }
        } else {
            while (moveCnt < 0) {
                if (idx == 1) {
                    idx = N
                } else {
                    idx--
                }

                if (!visited[idx]) {
                    moveCnt++
                }
            }
        }
    }
    answer.add(idx)

    // output
    for (num in answer) {
        print("$num ")
    }
}

// Solution 2 : Deque
fun main() {
    // input
    val scanner = Scanner(System.`in`)

    val N = scanner.nextInt()
    val deque = ArrayDeque<Paper>(N)
    for (idx in 1..N) {
        val value = scanner.nextInt()
        deque.add(Paper(idx, value))
    }

    // solution
    val answer = mutableListOf<Int>()
    while (!deque.isEmpty()) {
        val paper = deque.removeFirst()
        answer.add(paper.no)

        if (deque.isEmpty()) {
            break
        }

        if (paper.value > 0) {
            for (cnt in 1 until paper.value) {
                val tempPaper = deque.removeFirst()
                deque.addLast(tempPaper)
            }
        } else {
            for (cnt in 1 ..abs(paper.value)) {
                val tempPaper = deque.removeLast()
                deque.addFirst(tempPaper)
            }
        }
    }

    // output
    for (num in answer) {
        print("$num ")
    }
}

data class Paper(val no: Int, val value: Int)
