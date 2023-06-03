import kotlin.math.pow

fun main() {
    // input
    val (N, R) = readln().split(" ").map { it.toInt() }
    val size = 2.0.pow(N).toInt()
    val map = Array(size) { IntArray(size) }
    for (r in 0 until size) {
        val arr = readln().split(" ").map { it.toInt() }.toTypedArray()
        for (c in 0 until size) {
            map[r][c] = arr[c]
        }
    }

    val operations = mutableListOf<Pair<Int, Int>>()
    for (cnt in 1..R) {
        val (k, l) = readln().split(" ").map { it.toInt() }
        operations.add(Pair(k, l))
    }

    // solution
    for ((k, l) in operations) {
        val subSize = 2.0.pow(l).toInt()
        when (k) {
            1 -> {
                for (largeR in 0 until size step (subSize)) {
                    for (largeC in 0 until size step (subSize)) {
                        for (c in largeC until largeC + subSize) {
                            var lo = largeR
                            var hi = largeR + subSize - 1
                            while (lo < hi) {
                                val tmp = map[lo][c]
                                map[lo][c] = map[hi][c]
                                map[hi][c] = tmp
                                ++lo
                                --hi
                            }
                        }
                    }
                }
            }
            2 -> {
                for (largeR in 0 until size step (subSize)) {
                    for (largeC in 0 until size step (subSize)) {
                        for (r in largeR until largeR + subSize) {
                            var lo = largeC
                            var hi = largeC + subSize - 1
                            while (lo < hi) {
                                val tmp = map[r][lo]
                                map[r][lo] = map[r][hi]
                                map[r][hi] = tmp
                                ++lo
                                --hi
                            }
                        }
                    }
                }
            }
            3 -> {
                for (largeR in 0 until size step (subSize)) {
                    for (largeC in 0 until size step (subSize)) {
                        val q = ArrayDeque<Int>()
                        for (r in largeR until largeR + subSize) {
                            for (c in largeC until largeC + subSize) {
                                q.addLast(map[r][c])
                            }
                        }

                        for (c in largeC + subSize - 1 downTo largeC) {
                            for (r in largeR until largeR + subSize) {
                                map[r][c] = q.removeFirst()
                            }
                        }
                    }
                }
            }
            4 -> {
                for (largeR in 0 until size step (subSize)) {
                    for (largeC in 0 until size step (subSize)) {
                        val q = ArrayDeque<Int>()
                        for (r in largeR until largeR + subSize) {
                            for (c in largeC until largeC + subSize) {
                                q.addLast(map[r][c])
                            }
                        }

                        for (c in largeC until largeC + subSize) {
                            for (r in largeR + subSize - 1 downTo largeR) {
                                map[r][c] = q.removeFirst()
                            }
                        }
                    }
                }
            }
            5 -> {
                for (largeC in 0 until size step (subSize)) {
                    var lo = 0
                    var hi = size - subSize
                    while (lo < hi) {
                        val tmp = Array(subSize) { IntArray(subSize) }
                        for (r in 0 until subSize) {
                            for (c in 0 until subSize) {
                                tmp[r][c] = map[r + lo][c + largeC]
                            }
                        }

                        for (r in 0 until subSize) {
                            for (c in 0 until subSize) {
                                map[r + lo][c + largeC] = map[r + hi][c + largeC]
                            }
                        }

                        for (r in 0 until subSize) {
                            for (c in 0 until subSize) {
                                map[r + hi][c + largeC] = tmp[r][c]
                            }
                        }

                        lo += subSize
                        hi -= subSize
                    }
                }
            }
            6 -> {
                for (largeR in 0 until size step (subSize)) {
                    var lo = 0
                    var hi = size - subSize
                    while (lo < hi) {
                        val tmp = Array(subSize) { IntArray(subSize) }
                        for (r in 0 until subSize) {
                            for (c in 0 until subSize) {
                                tmp[r][c] = map[r + largeR][c + lo]
                            }
                        }

                        for (r in 0 until subSize) {
                            for (c in 0 until subSize) {
                                map[r + largeR][c + lo] = map[r + largeR][c + hi]
                            }
                        }

                        for (r in 0 until subSize) {
                            for (c in 0 until subSize) {
                                map[r + largeR][c + hi] = tmp[r][c]
                            }
                        }

                        lo += subSize
                        hi -= subSize
                    }
                }
            }
            7 -> {
                val q = ArrayDeque<Array<IntArray>>()
                for (largeR in 0 until size step (subSize)) {
                    for (largeC in 0 until size step (subSize)) {
                        val temp = Array(subSize) { IntArray(subSize) }
                        for (r in 0 until subSize) {
                            for (c in 0 until subSize) {
                                temp[r][c] = map[r + largeR][c + largeC]
                            }
                        }
                        q.addLast(temp)
                    }
                }

                for (largeC in size - subSize downTo 0 step (subSize)) {
                    for (largeR in 0 until size step (subSize)) {
                        val temp = q.removeFirst()
                        for (r in 0 until subSize) {
                            for (c in 0 until subSize) {
                                map[r + largeR][c + largeC] = temp[r][c]
                            }
                        }
                    }
                }
            }
            8 -> {
                val q = ArrayDeque<Array<IntArray>>()
                for (largeR in 0 until size step (subSize)) {
                    for (largeC in 0 until size step (subSize)) {
                        val temp = Array(subSize) { IntArray(subSize) }
                        for (r in 0 until subSize) {
                            for (c in 0 until subSize) {
                                temp[r][c] = map[r + largeR][c + largeC]
                            }
                        }
                        q.addLast(temp)
                    }
                }

                for (largeC in 0 until size step (subSize)) {
                    for (largeR in size - subSize downTo 0 step (subSize)) {
                        val temp = q.removeFirst()
                        for (r in 0 until subSize) {
                            for (c in 0 until subSize) {
                                map[r + largeR][c + largeC] = temp[r][c]
                            }
                        }
                    }
                }
            }
        }
    }

    // output
    val answer = StringBuilder()
    for (r in 0 until size) {
        for (c in 0 until size) {
            answer.append(map[r][c]).append(' ')
        }
        answer.append("\n")
    }
    print(answer.toString())
}
