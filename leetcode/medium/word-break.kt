/*
Solution 1 : BFS
Time Complexity : O(n^3 + mk) (n : length of s, m : length of wordDict, k : average length of the words in wordDict)
(Detail : BFS -> O(n^3) + Convert to HashSet -> O(mk))
Space Complexity : O(n + mk)
*/
class Solution {
    fun wordBreak(s: String, wordDict: List<String>): Boolean {
        // 1. convert wordDict to HashSet
        val words = wordDict.toHashSet()

        // 2. Init queue and visited array
        val queue = ArrayDeque<Int>()
        val visited = BooleanArray(s.length) { false }

        // 4. start bfs
        queue.add(0)
        while (queue.isNotEmpty()) {
            val start = queue.removeFirst()

            if (start == s.length) {
                return true
            }

            for (end in start + 1..s.length) {
                if (!visited[end - 1] && words.contains(s.substring(start, end))) {
                    visited[end - 1] = true
                    queue.addLast(end)
                }
            }
        }

        // 5. if we can't reach last node than return false.
        return false
    }
}

/*
Solution 2 : Dynamic Programming Top Down (DFS + Memorization)
Time Complexity : O(nmk) (n : length of s, m : length of wordDict, k : average length of the wordsin wordDict)
Space Complexity : O(n)
*/
private var n = 0
private lateinit var memo: IntArray
private lateinit var str: String
private lateinit var words: List<String>

class Solution {
    fun wordBreak(s: String, wordDict: List<String>): Boolean {
        str = s
        words = wordDict
        memo = IntArray(s.length) { -1 }
        return isPossible(s.length - 1)
    }

    private fun isPossible(idx: Int): Boolean {
        // base case
        if (idx < 0) {
            return true
        }

        if (memo[idx] != -1) {
            return memo[idx] == 1
        }

        for (word in words) {
            if (idx - word.length + 1 < 0) {
                continue
            }

            if (str.substring(idx - word.length + 1, idx + 1) == word && isPossible(idx - word.length)) {
                memo[idx] = 1
                return true
            }
        }

        memo[idx] = 0
        return false
    }
}

/*
Solution 3 : Dynamic Programming Bottom Up
Time Complexity : O(nmk) (n : length of s, m : length of wordDict, k : average length of the wordsin wordDict)
Space Complexity : O(n)
*/
class Solution {
    fun wordBreak(s: String, wordDict: List<String>): Boolean {
        val dp = BooleanArray(s.length) { false }
        
        for (i in s.indices) {
            for (word in wordDict) {
                if (i < word.length - 1) {
                    continue
                }
                
                if (i == word.length - 1 || dp[i - word.length]) {
                    if (s.substring(i - word.length + 1, i + 1) == word) {
                        dp[i] = true
                        break
                    }
                }
            }
        }
        
        return dp[s.length - 1]
    }
}

/*
Solution 3 - 2 : Optimize using trie data structer
Time Complexity : O(n^2 + mk) (n : s.length, m : wordDict.length k : average length of the word in wordDict)
*/
class Solution {
    fun wordBreak(s: String, wordDict: List<String>): Boolean {
        val trie = Trie()
        trie.addWords(wordDict)

        val dp = BooleanArray(s.length) { false }
        for (i in s.indices) {
            if (i != 0 && !dp[i - 1]) {
                continue
            }

            var curr = trie.getRootNode()
            for (j in i until s.length) {
                if (!curr.isChild(s[j])) {
                    break
                }

                curr = curr.getChild(s[j])
                if (curr.isLastChar()) {
                    dp[j] = true
                }
            }
        }

        return dp[s.length - 1]
    }
}

class Trie {

    private val root = Node(value = ' ')

    fun getRootNode() = root

    fun addWords(words: List<String>) {
        for (word in words) {
            addWord(word)
        }
    }

    private fun addWord(word: String) {
        var cur = root
        for (c in word.toCharArray()) {
            if (!cur.isChild(c)) {
                cur.insertChild(Node(value = c))
            }
            cur = cur.getChild(c)
        }
        cur.lastChar()
    }

    data class Node(
        val childs: MutableMap<Char, Node> = mutableMapOf(),
        val value: Char,
        var isEnd: Boolean = false
    ) {
        fun isChild(value: Char) = childs.contains(value)

        fun insertChild(child: Node) {
            childs[child.value] = child
        }

        fun getChild(value: Char) = childs[value]!!

        fun lastChar() {
            isEnd = true
        }

        fun isLastChar() = isEnd
    }
}

/*
Solution 4 : Dynamic Programming (Bottom-Up)
Time Complexity : O(nm) (n: s.length, m: wordDict.length
Space Complexity : O(n)
*/
class Solution {
    fun wordBreak(s: String, wordDict: List<String>): Boolean {
        // dp[i] ([i, s.length] 문자열의 wordDict 표현 가능 여부)
        val dp = BooleanArray(s.length + 1) { false }
        dp[s.length] = true

        for (i in s.length downTo 0) {
            for (word in wordDict) {
                if (i + word.length <= s.length && word == s.substring(i, i + word.length)) {
                    dp[i] = dp[i + word.length]
                }
                if (dp[i]) break
            }
        }
        return dp[0]
    }
}

/*
Solution 5 : DFS + Memorization
Time Complexity : O(n^2) (n: s.length)
Space Complexity : O(n^2)
*/
private lateinit var memo: IntArray
private lateinit var dict: Set<String>
private var n = 0

class Solution {
    fun wordBreak(s: String, wordDict: List<String>): Boolean {
        n = s.length
        dict = wordDict.toSet()
        memo = IntArray(n + 1) { -1 }

        return getAnswer(0, s)
    }

    private fun getAnswer(start: Int, s: String): Boolean {
        // base case
        if (start == n) {
            return true
        }

        for (i in 1..n - start) {
            if (dict.contains(s.substring(start, start + i))) {
                if (memo[start + i] == -1) {
                    memo[start + i] = if (getAnswer(start + i, s)) 1 else 0
                }

                if (memo[start + i] == 1) {
                    return true
                }
            }
        }
        return false
    }
}
