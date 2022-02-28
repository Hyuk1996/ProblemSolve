import java.util.*;

class Solution {
    
    private List<List<String>> lists = new ArrayList<>();
    private List<String> list = new ArrayList<>();
    
    
    public int solution(String[] user_id, String[] banned_id) {
        
        
        boolean[] check = new boolean[user_id.length];
        permutation(user_id, banned_id, 0, check);
        
        //중복제거 후 사용자 목록 개수 반환
        int answer = removeOverlap();
        return answer;
    }
    
    private void permutation(String[] user_id, String[] banned_id, int depth, boolean[] check) {
        if(depth == banned_id.length) {
            lists.add(new ArrayList(list));
            return;
        }
        
        for(int i = 0; i < user_id.length; ++i) {
            if(!check[i]) {
                if(possible(user_id[i], banned_id[depth])) {
                    list.add(user_id[i]);
                    check[i] = true;
                    permutation(user_id, banned_id, depth + 1, check);
                    list.remove(depth);
                    check[i] = false;
                }
            }
        }
    }
    
    private boolean possible(String u_id, String b_id) {
        if(u_id.length() != b_id.length()) {
            return false;
        }
        for(int i = 0; i < b_id.length(); ++i) {
            if(b_id.charAt(i) == '*') {
                continue;
            }
            
            if(b_id.charAt(i) != u_id.charAt(i)) {
                return false;
            }
        }
        return true;
    }
    
    private int removeOverlap() {
        Set<String> set = new HashSet<>();
        for(int i = 0; i < lists.size(); ++i) {
            Collections.sort(lists.get(i));
            StringBuilder sb = new StringBuilder();
            for(String s : lists.get(i)) {
                sb.append(s);
            }
            set.add(sb.toString());
        }
        return set.size();
    }
}
