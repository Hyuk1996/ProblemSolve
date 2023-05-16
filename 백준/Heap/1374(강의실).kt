package com.example.algorithm

import java.util.*

fun main() {
    // input
    val scanner = Scanner(System.`in`)
    val N = scanner.nextInt()

    val pq = PriorityQueue<Lecture> { o1, o2 -> o1.start.compareTo(o2.start) }
    for (i in 1..N) {
        val no = scanner.nextInt()
        val start = scanner.nextLong()
        val end = scanner.nextLong()

        pq.add(Lecture(no, start, end))
    }

    // solution
    var answer = 0
    val currentLectures = PriorityQueue<Lecture> { o1, o2 -> o1.end.compareTo(o2.end) }
    while (!pq.isEmpty()) {
        val newLecture = pq.poll()!!
        while (!currentLectures.isEmpty() && currentLectures.peek()!!.end <= newLecture.start) {
            currentLectures.poll()
        }
        currentLectures.add(newLecture)
        if (answer < currentLectures.size) {
            answer = currentLectures.size
        }
    }

    // output
    println(answer)
}

data class Lecture(val no: Int, val start: Long, val end: Long)
