import java.time.LocalDate
import java.time.format.DateTimeFormatter

class Solution {

    companion object {
        private val formatter = DateTimeFormatter.ofPattern("yyyy.MM.dd")
    }

    fun solution(today: String, terms: Array<String>, privacies: Array<String>): IntArray {
        val today = LocalDate.parse(today, formatter)

        val terms = terms.associate { term ->
            val tokens = term.split(" ")
            tokens[0] to (tokens[1].toInt())
        }

        var answer = mutableListOf<Int>()
        for (i in privacies.indices) {
            val no = i + 1

            val tokens = privacies[i].split(" ")
            var date = LocalDate.parse(tokens[0], formatter)
            val term = tokens[1]

            date = date.plusMonths(terms[term]!!.toLong())

            if (date <= today) {
                answer.add(no)
            }
        }

        answer.sort()
        return answer.toIntArray()
    }
}
