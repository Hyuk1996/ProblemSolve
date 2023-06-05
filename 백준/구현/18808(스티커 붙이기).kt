fun main() {
    // input
    val (N, M, K) = readln().split(" ").map { it.toInt() }
    val notebook = Array(N) { IntArray(M) { 0 } }

    val stickers = ArrayDeque<Array<IntArray>>()
    for (i in 1..K) {
        val (R, C) = readln().split(" ").map { it.toInt() }
        val sticker = Array(R) { IntArray(C) { 0 } }
        for (r in 0 until R) {
            val info = readln().split(" ").map { it.toInt() }
            for (c in 0 until C) {
                sticker[r][c] = info[c]
            }
        }
        stickers.addLast(sticker)
    }
    
    // solution
    while (stickers.isNotEmpty()) {
        var sticker = stickers.removeFirst()

        for (rotate in 1..4) {
            // validate can post
            var startR = 0
            var startC = 0
            var canPost = false
            while (startR + sticker.size <= N && startC + sticker[0].size <= M) {
                var isDuplicate = false
                for (r in startR until startR + sticker.size) {
                    for (c in startC until startC + sticker[0].size) {
                        if (sticker[r - startR][c - startC] == 1 && notebook[r][c] == 1) {
                            isDuplicate = true
                            break
                        }
                    }
                    if (isDuplicate) {
                        break
                    }
                }

                if (!isDuplicate) {
                    canPost = true
                    break
                } else {
                    if (startC + sticker[0].size < M) {
                        startC++
                    } else {
                        startR++
                        startC = 0
                    }
                }
            }

            // post sticker
            if (canPost) {
                for (r in startR until startR + sticker.size) {
                    for (c in startC until startC + sticker[0].size) {
                        if (sticker[r - startR][c - startC] == 1) {
                            notebook[r][c] = 1
                        }
                    }
                }
                break
            }

            // rotate sticker
            val que = ArrayDeque<Int>()
            for (r in 0 until sticker.size) {
                for (c in 0 until sticker[0].size) {
                    que.addLast(sticker[r][c])
                }
            }

            sticker = Array(sticker[0].size) { IntArray(sticker.size) { 0 } }

            for (c in sticker[0].size - 1 downTo 0) {
                for (r in 0 until sticker.size) {
                    sticker[r][c] = que.removeFirst()
                }
            }
        }
    }

    var answer = 0
    for (r in 0 until N) {
        for (c in 0 until M) {
            answer += notebook[r][c]
        }
    }

    // output
    println(answer)
}
