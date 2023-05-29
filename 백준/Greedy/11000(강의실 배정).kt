import java.util.PriorityQueue

fun main() {
    // input
    val N = readln().toInt()
    val tasks = mutableListOf<Task>()
    for (i in 1..N) {
        val (startAt, endAt) = readln().split(" ").map { it.toInt() }
        tasks.add(Task(startAt, endAt))
    }

    // solution
    tasks.sortWith(compareBy({ it.startAt }, { it.endAt }))
    val pq = PriorityQueue<Int>()

    var answer = 0
    for (task in tasks) {
        while (pq.isNotEmpty()) {
            if (task.startAt >= pq.peek()) {
                pq.poll()
            } else {
                break
            }
        }
        pq.add(task.endAt)

        if (pq.size > answer) {
            answer = pq.size
        }
    }

    // output
    println(answer)
}

data class Task(val startAt: Int, val endAt: Int)
