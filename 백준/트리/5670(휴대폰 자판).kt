fun main() = with(System.`in`.bufferedReader()) {
    var n = readLine()
    while (n != null) {
        val words = mutableListOf<String>()
        for (i in 1..n.toInt()) {
            val word = readLine()
            words.add(word)
        }

        val trie = Trie()
        for (word in words) {
            trie.insert(word)
        }

        var totalCnt = 0
        for (word in words) {
            totalCnt += trie.countClick(word)
        }

        println(String.format("%.2f", totalCnt.toDouble() / words.size))

        n = readLine()
    }
}

class Trie {
    private val root = Node(' ', false, mutableMapOf())

    fun insert(word: String) {
        var curNode = root
        for (key in word.toCharArray()) {
            val findNode = findChild(key, curNode)

            if (findNode == null) {
                val newNode = Node(key, false, mutableMapOf())
                curNode.child[key] = newNode
                curNode = newNode
            } else {
                curNode = findNode
            }
        }

        curNode.isEnd = true
    }

    private fun findChild(key: Char, curNode: Node): Node? = curNode.child[key]

    fun countClick(word: String): Int {
        var cnt = 0
        var curNode = root
        for (i in word.indices) {
            val key = word[i]

            if (i == 0) {
                cnt++
            } else {
                if (curNode.child.size > 1 || (curNode.child.size == 1 && curNode.isEnd)) {
                    cnt++
                }
            }

            curNode = findChild(key, curNode)!!
        }
        return cnt
    }

    data class Node(val key: Char, var isEnd: Boolean, val child: MutableMap<Char, Node>)
}
