import java.util.*;

class Solution {
    public String solution(String number, int k) {
        
        int answerLen = number.length() - k;
        
        Stack<Integer> stack = new Stack<>();
        for (int i = 0; i < number.length(); ++i) {
            int num = number.charAt(i) - '0';
            while (!stack.isEmpty() && stack.peek() < num && k > 0) {
                stack.pop();
                k--;
            }
            stack.push(num);
        }
        
        StringBuilder answer = new StringBuilder();
        for (int i = 0; i < answerLen; ++i) {
            answer.append(stack.get(i));
        }
        
        return answer.toString();
    }
}
