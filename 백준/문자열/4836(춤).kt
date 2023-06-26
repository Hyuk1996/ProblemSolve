fun main() = with(System.`in`.bufferedReader()) {
    while (true) {
        val input = readLine() ?: break

        val actions = input.split(" ").toMutableList()

        val violates = mutableListOf<Int>()

        // validate rule 1
        var pass = true
        for (idx in actions.indices) {
            if (actions[idx] == "dip") {
                var check = false

                if (idx - 1 >= 0) {
                    if (actions[idx - 1] == "jiggle") {
                        check = true
                    }
                }
                if (idx - 2 >= 0) {
                    if (actions[idx - 2] == "jiggle") {
                        check = true
                    }
                }
                if (idx + 1 < actions.size) {
                    if (actions[idx + 1] == "twirl") {
                        check = true
                    }
                }

                if (!check) {
                    actions[idx] = "DIP"
                    pass = false
                }
            }
        }

        if (!pass) {
            violates.add(1)
        }

        // validate rule 2
        pass = true
        if (actions.size < 3) {
            pass = false
        } else {
            if (!(actions[actions.size - 1] == "clap" && actions[actions.size - 2] == "stomp" && actions[actions.size - 3] == "clap")) {
                pass = false
            }
        }

        if (!pass) {
            violates.add(2)
        }

        // validate rule 3
        pass = true
        var twirlCnt = 0
        var hopCnt = 0
        for (action in actions) {
            if (action == "twirl") {
                twirlCnt++
            }
            if (action == "hop") {
                hopCnt++
            }
        }
        if (twirlCnt > 0 && hopCnt == 0) {
            pass = false
        }

        if (!pass) {
            violates.add(3)
        }

        // validate rule 4
        if (actions[0] == "jiggle") {
            violates.add(4)
        }

        // validate rule 5
        pass = false
        for (action in actions) {
            if (action == "dip" || action == "DIP") {
                pass = true
                break
            }
        }
        if (!pass) {
            violates.add(5)
        }

        // output
        if (violates.isEmpty()) {
            print("form ok: ")
            for (action in actions) {
                print("$action ")
            }
            println()
        } else if (violates.size == 1) {
            print("form error ${violates[0]}: ")
            for (action in actions) {
                print("$action ")
            }
            println()
        } else {
            print("form errors ")
            for (idx in 0 until violates.size - 2) {
                print("${violates[idx]}, ")
            }
            print("${violates[violates.size - 2]} and ${violates[violates.size - 1]}: ")
            for (action in actions) {
                print("$action ")
            }
            println()
        }
    }
}
