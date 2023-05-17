package com.example.algorithm

import kotlin.math.pow
import kotlin.math.sqrt

fun main() {
    // input
    val G = readln().toInt()

    // solution
    var prevWeight = 1
    var isContinue = true
    var answers = mutableListOf<Int>()
    do {
        val curWeight = sqrt(G + prevWeight.toDouble().pow(2.0))

        if (curWeight * curWeight == curWeight.toInt().toDouble().pow(2.0)) {
            answers.add(curWeight.toInt())
        }

        if (((prevWeight + 2).toDouble().pow(2) - (prevWeight + 1).toDouble().pow(2)).toInt() > G) {
            isContinue = false
        } else {
            prevWeight++
        }
    } while (isContinue)

    // output
    if (answers.isEmpty()) {
        println(-1)
    } else {
        for (answer in answers) {
            println(answer)
        }
    }
}
