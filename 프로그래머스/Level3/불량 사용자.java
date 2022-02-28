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

//비트 마스킹 이용
import java.util.*;

class Solution {
    
    private Set<Integer> answer = new HashSet<>();
    boolean[] check;
    
    
    public int solution(String[] user_id, String[] banned_id) {
        
        
        check = new boolean[user_id.length];
        permutation(user_id, banned_id, 0, 0);
        
        return answer.size();
    }
    
    private void permutation(String[] user_id, String[] banned_id, int depth, int bit) {
        if(depth == banned_id.length) {
            answer.add(bit); //최종 선택된 user_id 정보 저장
            return;
        }
        
        for(int i = 0; i < user_id.length; ++i) {
            if(((bit >> i) & 1) != 1) { //비트 마스킹을 이용해 i번째 user_id가 선택되었는 확인
                String regx = banned_id[depth].replace("*", "[\\w\\d]");
                if(user_id[i].matches(regx)) {
                    permutation(user_id, banned_id, depth + 1, (bit | 1 << i)); // 비트 마스킹을 이용해 i번째 아이디가 선택됨을 체크
                }
            }
        }
    }
    
}
