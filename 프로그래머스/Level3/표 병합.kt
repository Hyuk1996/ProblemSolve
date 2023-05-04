// Solution 1 - Implementation
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

// Solution 2 - using DSU (Disjoint Set Union) data structure
class Solution {
    private val contents = Array(51) { Array(51) { "EMPTY" } }
    private val representative = Array(51) { r ->
        Array(51) { c ->
            Position(r, c)
        }
    }

    fun solution(commands: Array<String>): Array<String> {
        var answer = mutableListOf<String>()

        for (command in commands) {
            val tokens = command.split(" ")
            when (tokens[0]) {
                "UPDATE" -> {
                    if (tokens.size == 4) {
                        val r = tokens[1].toInt()
                        val c = tokens[2].toInt()
                        val value = tokens[3]

                        val root = find(Position(r, c))
                        contents[root.r][root.c] = value
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
                }

                "MERGE" -> {
                    val r1 = tokens[1].toInt()
                    val c1 = tokens[2].toInt()
                    val r2 = tokens[3].toInt()
                    val c2 = tokens[4].toInt()

                    val pos1 = Position(r1, c1)
                    val rootPos1 = find(pos1)

                    val pos2 = Position(r2, c2)
                    val rootPos2 = find(pos2)

                    // merge value
                    if (contents[rootPos1.r][rootPos1.c] == "EMPTY" && contents[rootPos2.r][rootPos2.c] != "EMPTY") {
                        contents[rootPos1.r][rootPos1.c] = contents[rootPos2.r][rootPos2.c]
                    }
                    union(rootPos1, rootPos2)
                }

                "UNMERGE" -> {
                    val r = tokens[1].toInt()
                    val c = tokens[2].toInt()

                    val root = find(Position(r, c))
                    val value = contents[root.r][root.c]


                    val unmergedMember = mutableListOf<Position>()
                    for (r in 1..50) {
                        for (c in 1..50) {
                            if (find(Position(r, c)) == root) {
                                unmergedMember.add(Position(r, c))
                            }
                        }
                    }

                    unmergedMember.forEach { member ->
                        representative[member.r][member.c] = Position(member.r, member.c)
                        contents[member.r][member.c] = "EMPTY"
                    }

                    contents[r][c] = value
                }

                "PRINT" -> {
                    val r = tokens[1].toInt()
                    val c = tokens[2].toInt()

                    val root = find(Position(r, c))
                    answer.add(contents[root.r][root.c])
                }

                else -> throw IllegalArgumentException("wrong commands")
            }
        }
        return answer.toTypedArray()
    }

    private fun union(pos1: Position, pos2: Position) {
        val root1 = find(pos1)
        val root2 = find(pos2)

        if (root1 == root2) {
            return
        }

        representative[root2.r][root2.c] = Position(root1.r, root1.c)
    }

    private fun find(pos: Position): Position {
        if (representative[pos.r][pos.c] == pos) {
            return Position(pos.r, pos.c)
        }

        representative[pos.r][pos.c] = find(representative[pos.r][pos.c])
        return Position(representative[pos.r][pos.c].r, representative[pos.r][pos.c].c)
    }

    data class Position(val r: Int, val c: Int)
}

