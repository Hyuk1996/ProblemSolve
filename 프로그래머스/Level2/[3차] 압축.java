import java.util.*;

class Solution {
    
    private static Map<String, Integer> dict;
    
    public int[] solution(String msg) {
        
        //사전 만들기
        makeDictionary();
        
        //압축
        int[] answer = compress(msg);
    
        return answer;
    }
    
    private static void makeDictionary() {
        
        dict = new HashMap<>();
        
        char word = 'A';
        for(int i = 1; i <= 26; ++i) {
            dict.put(String.valueOf(word++), i);
        }
    }
    
    private static int[] compress(String msg) {
        
        List<Integer> answer = new ArrayList<>();
        
        while(true) {
            String w = findW(msg);
            
            answer.add(dict.get(w));
            if(w.length() == msg.length()) {
                break;
            }
            
            msg = msg.substring(w.length());
            String newWord = w + msg.substring(0, 1);
            int newIdx = dict.size() + 1;
            dict.put(newWord, newIdx);
        }
        
        return getAnswer(answer);
    }
    
    private static String findW(String msg) {
        int start = 0;
        int end = 1;
        while(true) {
            if(end > msg.length() || dict.get(msg.substring(start, end)) == null) {
                end--;
                break;
            }
            end++;
        }
        return msg.substring(start, end);
    }
    
    private static int[] getAnswer(List<Integer> list) {
        int[] answer = new int[list.size()];
        for(int i = 0; i < list.size(); ++i) {
            answer[i] = list.get(i);
        }
        return answer;
    }
    
}
