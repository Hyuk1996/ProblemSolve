import kotlin.math.pow

class Solution {
    fun solution(numbers: LongArray): IntArray {
        var answers = mutableListOf<Int>()

        for (number in numbers) {
            val binary = convertToBinary(number)
            addPadding(binary)

            if (canMakeBinaryTree(binary.toIntArray(), 0, binary.size)) {
                answers.add(1)
            } else {
                answers.add(0)
            }
        }

        return answers.toIntArray()
    }

    // [startIdx, endIdx)
    private fun canMakeBinaryTree(binary: IntArray, startIdx: Int, endIdx: Int): Boolean {
        //base case
        if (endIdx - startIdx == 1) {
            return true
        }

        val middleIdx = startIdx + ((endIdx - startIdx) / 2)
        val parent = binary[middleIdx]

        val canMakeLeftSubTree = canMakeBinaryTree(binary, startIdx, middleIdx)
        val canMakeRightSubTree = canMakeBinaryTree(binary, middleIdx + 1, endIdx)
        if (!(canMakeLeftSubTree && canMakeRightSubTree)) {
            return false
        }

        if (parent == 0) {
            val leftChild = binary[startIdx + (((endIdx - startIdx) / 2) / 2)]
            val rightChild = binary[(middleIdx + 1) + (((endIdx - startIdx) / 2) / 2)]
            if (leftChild == 1 || rightChild == 1) {
                return false
            }
        }

        return true
    }

    private fun convertToBinary(number: Long): ArrayDeque<Int> {
        val deque = ArrayDeque<Int>()
        var a = number
        while (a != 0L) {
            deque.addFirst((a % 2L).toInt())
            a /= 2L
        }

        return deque
    }

    private fun addPadding(binary: ArrayDeque<Int>) {
        val binaryLen = binary.size.toLong()

        var height = 1.0

        while (true) {
            if ((2.0.pow(height) - 1.0).toLong() >= binaryLen) {
                break
            }
            height++
        }

        val finalLen = 2.0.pow(height) - 1.0
        val diffLen = (finalLen - binaryLen).toLong()
        for (i in 0 until diffLen) {
            binary.addFirst(0)
        }
    }
}
