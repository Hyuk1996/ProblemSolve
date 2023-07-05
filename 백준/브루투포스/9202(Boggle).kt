private val boggle = Array(4) { CharArray(4) }
private val visited = Array(4) { BooleanArray(4) { false } }
private val dr = arrayOf(-1, 0, 1, -1, 1, -1, 0, 1)
private val dc = arrayOf(-1, -1, -1, 0, 0, 1, 1, 1)

fun main() {
    val w = readln().toInt()
    val dict = Array(w) { "" }
    for (i in 0 until w) {
        dict[i] = readln()
    }

    // order by dictionary order
    dict.sort()

    readln()

    var b = readln().toInt()
    while (true) {
        for (r in 0..3) {
            val columns = readln()
            for (c in 0..3) {
                boggle[r][c] = columns[c]
            }
        }

        var maxScore = 0
        var maxLengthWord = ""
        var count = 0

        for (word in dict) {
            var exist = false
            for (r in 0..3) {
                for (c in 0..3) {
                    if (boggle[r][c] == word[0]) {
                        // init visited
                        for (r in 0..3) {
                            for (c in 0..3) {
                                visited[r][c] = false
                            }
                        }

                        // search word
                        visited[r][c] = true
                        val sb = StringBuilder().append(boggle[r][c])
                        if (findWord(r, c, sb, word)) {
                            maxScore += when (word.length) {
                                1, 2 -> 0
                                3, 4 -> 1
                                5 -> 2
                                6 -> 3
                                7 -> 5
                                8 -> 11
                                else -> throw IllegalArgumentException()
                            }

                            if (maxLengthWord.length < word.length) {
                                maxLengthWord = word
                            }

                            ++count

                            exist = true
                            break
                        }
                    }
                }
                if (exist) {
                    break
                }
            }
        }

        println("$maxScore $maxLengthWord $count")

        if (--b == 0) {
            break
        } else {
            readln()
        }
    }
}

fun findWord(r: Int, c: Int, curWord: StringBuilder, word: String): Boolean {
    if (curWord.length == word.length) {
        return true
    }

    for (d in 0..7) {
        val nextR = r + dr[d]
        val nextC = c + dc[d]

        if (nextR in 0..3 && nextC in 0..3) {
            if (!visited[nextR][nextC] && boggle[nextR][nextC] == word[curWord.length]) {

                visited[nextR][nextC] = true
                curWord.append(boggle[nextR][nextC])

                if (findWord(nextR, nextC, curWord, word)) {
                    return true
                }

                visited[nextR][nextC] = false
                curWord.deleteCharAt(curWord.length - 1)
            }
        }
    }
    return false
}
