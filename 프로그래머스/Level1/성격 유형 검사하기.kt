class Solution {
    fun solution(survey: Array<String>, choices: IntArray): String {

        val score = mutableMapOf("RT" to 0, "CF" to 0, "JM" to 0, "AN" to 0)

        choices.forEachIndexed { index, choice ->
            if (score.containsKey(survey[index])) {
                score[survey[index]] = score[survey[index]]!! + (choice - 4)
            } else {
                score[survey[index].reversed()] = score[survey[index].reversed()]!! - (choice - 4)
            }
        }

        val answer = score.map { (key, value) ->
            if (value > 0) key[1] else key[0]
        }.joinToString("")

        return answer.toString()
    }
}
