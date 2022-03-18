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

//재귀 풀이
import java.io.*;
import java.util.*;

public class Main {

    static String str;
    static boolean[] visit;

    public static void main(String[] args) throws IOException {
        input();

        visit = new boolean[str.length()];
        System.out.println(dfs(0));
    }

    static void input() throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        str = br.readLine();
    }

    static int dfs(int start) {
        int len = 0;

        for(int i = start; i < str.length(); ++i) {
            if(visit[i]) {
                continue;
            }

            visit[i] = true;
            if(str.charAt(i) == '(') {
                len--;
                len += (str.charAt(i - 1) - '0') * dfs(i + 1);
            } else if(str.charAt(i) == ')') {
                return len;
            } else {
                len++;
            }
        }
        return len;
    }
}
