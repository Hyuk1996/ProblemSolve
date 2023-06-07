fun main() {
    // input
    val (N, M) = readln().split(" ").map { it.toInt() }
    val knowtruth = readln().split(" ").map { it.toInt() }.toIntArray()
    val parties = mutableMapOf<Int, Set<Int>>()
    for (i in 1..M) {
        val participants = readln().split(" ").map { it.toInt() }.toIntArray()
        val participantsSet = mutableSetOf<Int>()
        for (j in 1 until participants.size) {
            participantsSet.add(participants[j])
        }
        parties[i] = participantsSet
    }

    // solution
    val persons = mutableSetOf<Int>()
    for (i in 1 until knowtruth.size) {
        persons.add(knowtruth[i])
    }

    while (parties.isNotEmpty()) {
        // chose participate party
        var partyNo = -1
        for (party in parties) {
            for (person in persons) {
                if (party.value.contains(person)) {
                    partyNo = party.key
                    break
                }
            }
            if (partyNo != -1) {
                break
            }
        }

        if (partyNo == -1) {
            break
        }

        // participate party
        for (person in parties[partyNo]!!) {
            persons.add(person)
        }
        parties.remove(partyNo)
    }

    // output
    println(parties.size)
}
