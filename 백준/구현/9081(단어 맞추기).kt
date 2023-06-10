fun main() {
    // input
    var T = readln().toInt()
    val words = mutableListOf<String>()
    val answers = mutableListOf<String>()

    while (T-- > 0) {
        words.add(readln())
    }

    // solution
    for (word in words) {

        // find index that would be changed
        val chars = mutableListOf<Char>()
        var changeIdx = -1
        for (idx in word.length - 1 downTo 1) {
            if (word[idx] > word[idx - 1]) {
                chars.add(word[idx])
                chars.add(word[idx - 1])
                changeIdx = idx - 1
                break
            }
            chars.add(word[idx])
        }

        // if last word than nothing changed
        if (changeIdx == -1) {
            answers.add(word)
            continue
        }

        // make nextWord
        var firstChar = chars.max()
        for (char in chars) {
            if (char > word[changeIdx]) {
                firstChar = minOf(firstChar, char)
            }
        }
        chars.remove(firstChar)
        chars.sort()

        val nextWord = StringBuilder()
        for (i in 0 until changeIdx) {
            nextWord.append(word[i])
        }
        nextWord.append(firstChar)
        for (char in chars) {
            nextWord.append(char)
        }

        answers.add(nextWord.toString())
    }

    // output
    for (answer in answers) {
        println(answer)
    }
}
