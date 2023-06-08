
// solution using disjoint-set
private lateinit var parents: IntArray
private lateinit var sizes: IntArray

fun main() {
    // input
    val (N, M) = readln().split(" ").map { it.toInt() }

    val knows = readln().split(" ").map { it.toInt() }.toMutableList()
    knows.removeFirst()

    val parties = mutableMapOf<Int, MutableList<Int>>()
    for (i in 1..M) {
        val participants = readln().split(" ").map { it.toInt() }.toMutableList()
        participants.removeFirst()
        parties[i] = participants
    }

    // solution
    parents = IntArray(N + 1) { it }
    sizes = IntArray(N + 1) { 1 }

    for (party in parties) {
        val people = party.value
        val p1 = people[0]
        for (p2 in 1 until people.size) {
            union(p1, people[p2])
        }
    }
    

    var answer = 0
    for (party in parties) {
        val root = find(party.value[0])
        var canLie = true
        for (p in knows) {
            if (root == find(p)) {
                canLie = false
                break
            }
        }
        if (canLie) {
            answer++
        }
    }

    // output
    println(answer)
}

fun union(v: Int, u: Int) {
    val rootV = find(v)
    val rootU = find(u)

    if (rootV == rootU) {
        return
    }

    if (sizes[rootV] >= sizes[rootU]) {
        parents[rootU] = rootV
        sizes[rootV] += sizes[rootU]
    } else {
        parents[rootV] = rootU
        sizes[rootU] += sizes[rootV]
    }
}

fun find(v: Int): Int {
    if (parents[v] == v) {
        return v
    }

    parents[v] = find(parents[v])
    return parents[v]
}


// solution using hashset
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
