// Solution1 : bottom-up
class Solution {
    fun fib(n: Int): Int {
        if (n < 2) {
            return n
        }
        
        var a = 1
        var b = 0
        var c = 0
        for (i in 2 .. n) {
            c = a + b
            b = a
            a = c
        }
        return c
    }
}
