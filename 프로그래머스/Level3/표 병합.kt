class Solution {
    data class Position(
        val r: Int,
        val c: Int
    )

    fun solution(commands: Array<String>): Array<String> {
        var answer = mutableListOf<String>()

        val contents = Array(51) { Array(51) { "EMPTY" } }
        val merged = Array(51) { Array(51) { Position(-1, -1) } }
        for (r in 1..50) {
            for (c in 1..50) {
                merged[r][c] = Position(r, c)
            }
        }

        for (command in commands) {
            val tokens = command.split(" ")
            val operate = tokens[0]
            if (operate == "UPDATE") {
                if (tokens.size == 4) {
                    val r = tokens[1].toInt()
                    val c = tokens[2].toInt()
                    val value = tokens[3]

                    contents[merged[r][c].r][merged[r][c].c] = value
                } else {
                    val prevValue = tokens[1]
                    val nextValue = tokens[2]

                    for (r in 1..50) {
                        for (c in 1..50) {
                            if (contents[r][c] == prevValue) {
                                contents[r][c] = nextValue
                            }
                        }
                    }
                }
            } else if (operate == "MERGE") {
                val r1 = tokens[1].toInt()
                val c1 = tokens[2].toInt()
                val r2 = tokens[3].toInt()
                val c2 = tokens[4].toInt()

                // merge value
                if (contents[merged[r1][c1].r][merged[r1][c1].c] == "EMPTY" && contents[merged[r2][c2].r][merged[r2][c2].c] != "EMPTY") {
                    contents[merged[r1][c1].r][merged[r1][c1].c] = contents[merged[r2][c2].r][merged[r2][c2].c]
                }

                // update merge state
                val rootPosition = Position(merged[r2][c2].r, merged[r2][c2].c)
                for (r in 1..50) {
                    for (c in 1..50) {
                        if (merged[r][c] == rootPosition) {
                            merged[r][c] = Position(merged[r1][c1].r, merged[r1][c1].c)
                        }
                    }
                }
            } else if (operate == "UNMERGE") {
                val r = tokens[1].toInt()
                val c = tokens[2].toInt()
                val tmpValue = contents[merged[r][c].r][merged[r][c].c]

                val rootPosition = Position(merged[r][c].r, merged[r][c].c)
                for (r in 1..50) {
                    for (c in 1..50) {
                        if (merged[r][c] == rootPosition) {
                            merged[r][c] = Position(r, c)
                            contents[r][c] = "EMPTY"
                        }
                    }
                }

                contents[r][c] = tmpValue
            } else if (operate == "PRINT") {
                val r = tokens[1].toInt()
                val c = tokens[2].toInt()

                answer.add(contents[merged[r][c].r][merged[r][c].c])
            }
        }

        return answer.toTypedArray()
    }
}
