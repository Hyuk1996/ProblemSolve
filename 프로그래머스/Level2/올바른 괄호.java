import java.util.*;

class Solution {
    boolean solution(String s) {
        
        Stack<Character> stack = new Stack<>();
        for(int i = 0; i < s.length(); ++i) {
            char c = s.charAt(i);
            if(c == '(') {
                stack.push(c);
            } else {
                if(stack.empty()) {
                    return false;
                } else {
                    stack.pop();
                }
            }
        }
        
        if(stack.empty()) {
            return true;
        } else {
            return false;
        }
    }
}

//Stack을 사용하지 않는 풀이 (메모리적으로 더 효율적인 풀이)
class Solution {
    boolean solution(String s) {

        int count = 0;
        for(int i = 0; i < s.length(); ++i) {
            if(s.charAt(i) == '(') {
                count++;
            } else {
                if(count == 0) {
                    return false;
                }
                count--;
            }
        }
        
        if(count == 0) {
            return true;
        } else {
            return false;
        }
    }
}
