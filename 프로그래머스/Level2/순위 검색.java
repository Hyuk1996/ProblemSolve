import java.util.*;

class Solution {
    
    private int[] kinds = {3, 2, 2, 2};
    
    private Map<String, List<Integer>> store = new HashMap<>();
    
    public int[] solution(String[] info, String[] query) {
        
        //모든 조합의 맵 만들기
        initMap(new StringBuilder(), 0);
        
        //info 정보를 맵에 저장하기
        saveInfos(info);
        
        //query 검색하기
        int[] answer = new int[query.length];
        int index = 0;
        for (String q : query) {
            q = q.replace("and", "");
            q = q.replace("  ", " ");
            String[] token = q.split(" ");
            
            List<String> keys = getKeys(
                convertLang(token[0]),
                convertPos(token[1]),
                convertCareer(token[2]),
                convertSoulFood(token[3])
            );
            
            int score = Integer.valueOf(token[4]);
            int cnt = 0;
            for (String key : keys) {
                List<Integer> data = store.get(key);
                cnt += data.size() - binarySearch(data, score);;
            }
            answer[index++] = cnt;
        }
        
        return answer;
    }
    
    private void initMap(StringBuilder sb, int depth) {
        if (depth == 4) {
            store.put(sb.toString(), new ArrayList<>());
            return;
        }
        
        for (int i = 0; i < kinds[depth]; ++i) {
            sb.append(i);
            initMap(sb, depth + 1);
            sb.deleteCharAt(depth);
        }
    }
    
    private void saveInfos(String[] infos) {
        for (String info : infos) {
        String[] token = info.split(" ");
            
        String lang = convertLang(token[0]);
        String pos = convertPos(token[1]);
        String career = convertCareer(token[2]);
        String soulFood = convertSoulFood(token[3]);
            
        int score = Integer.valueOf(token[4]);
            
        String key = new StringBuilder()
            .append(lang)
            .append(pos)
            .append(career)
            .append(soulFood)
            .toString();
            
            store.get(key).add(score);
        }
        
        for (String key : store.keySet()) {
            Collections.sort(store.get(key));
        }
    }
    
    private List<String> getKeys(String lang, String pos, String career, String soulFood) {
        String[] cond = new String[] {lang, pos, career, soulFood};
            
        List<String> keys = new ArrayList<>();
        getKey(keys, cond, new StringBuilder(), 0);
        
        return keys;
    }
    
    private void getKey(List<String> keys, String[] cond, StringBuilder key, int depth) {
        if (depth == 4) {
            keys.add(key.toString());
            return;
        }
        
        if (cond[depth].equals("-1")) {
            for (int i = 0; i < kinds[depth]; ++i) {
                key.append(i);
                getKey(keys, cond, key, depth + 1);
                key.deleteCharAt(depth);
            }
        } else {
            key.append(cond[depth]);
            getKey(keys, cond, key, depth + 1);
            key.deleteCharAt(depth);
        }
    }
    
    private String convertLang(String lang) {
        if (lang.equals("cpp")) {
            return "0";
        }
        if (lang.equals("java")) {
            return "1";
        }
        if (lang.equals("python")) {
            return "2";
        }
        
        return "-1";
    }
    
    private String convertPos(String pos) {
        if (pos.equals("backend")) {
            return "0";
        }
        if (pos.equals("frontend")) {
            return "1";
        }
        
        return "-1";
    }
    
    private String convertCareer(String career) {
        if (career.equals("junior")) {
            return "0";
        }
        if (career.equals("senior")) {
            return "1";
        }
        
        return "-1";
    }
    
    private String convertSoulFood(String soulFood) {
        if (soulFood.equals("chicken")) {
            return "0";
        }
        if (soulFood.equals("pizza")) {
            return "1";
        }
        
        return "-1";
    }
    
    private int binarySearch(List<Integer> data, int score) {
            
        int lo = 0;
        int hi = data.size() - 1;
        
        if (data.size() == 0) {
            return 0;
        }
        if (data.get(lo) >= score) {
            return lo;
        }
        if (data.get(hi) < score) {
            return data.size();
        }
         
        while (lo + 1 < hi) {
            int mid = lo + (hi - lo) / 2;
            if (data.get(mid) >= score) {
                hi = mid;
            } else {
                lo = mid;
            }
        }
        return hi;
    }
}
