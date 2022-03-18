import java.io.*;
import java.util.*;

public class Main {

    static String str;

    public static void main(String[] args) throws IOException {
        input();

        Deque<Integer> stack = new ArrayDeque<>();
        for(int i = 0; i < str.length(); ++i) {
            if(str.charAt(i) == ')') {
                int tmp = 0;
                while(!stack.isEmpty()) {
                    if(stack.getLast() == -1) {
                        stack.removeLast();
                        break;
                    }
                    tmp += stack.getLast();
                    stack.removeLast();
                }

                tmp *= stack.getLast();
                stack.removeLast();
                stack.addLast(tmp);

            } else if(str.charAt(i) == '(') {
                stack.removeLast();
                stack.addLast(str.charAt(i - 1) - '0');
                stack.addLast(-1);
            } else {
                stack.addLast(1);
            }
        }

        int answer = 0;
        while(!stack.isEmpty()) {
            answer += stack.getLast();
            stack.removeLast();
        }
        System.out.println(answer);
    }

    static void input() throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        str = br.readLine();
    }
}
