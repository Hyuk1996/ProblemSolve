fun main() {
    // input
    val sound = readln()

    // solution
    val result = sound.matches(Regex("(100+1+|01)*"))

    // output
    println("${if (result) "SUBMARINE" else "NOISE"}")
}
