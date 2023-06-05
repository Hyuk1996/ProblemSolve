fun main() {
    // input
    val text = readln()

    // solution
    val cnt = IntArray(26) { 0 }
    for (i in text.indices) {
        ++cnt[text[i] - 'a']
    }

    // output
    for (i in cnt.indices) {
        print("${cnt[i]} ")
    }
}
