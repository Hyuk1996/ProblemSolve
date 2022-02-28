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
                String regx = banned_id[depth].replace("*", "[\\w\\d]");
                if(user_id[i].matches(regx)) {
                    list.add(user_id[i]);
                    check[i] = true;
                    permutation(user_id, banned_id, depth + 1, check);
                    list.remove(depth);
                    check[i] = false;
                }
            }
        }
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
