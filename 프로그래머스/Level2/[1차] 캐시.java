import java.util.HashMap;
import java.util.Map;

class Solution {
    
    private static final int MAX = 100000;
    
    public int solution(int cacheSize, String[] cities) {
        int answer = 0;
        
        if(cacheSize == 0) {
            answer = cities.length * 5;
            return answer;
        }
        
        Map<String, Integer> cache = new HashMap<>();
        for(int i=0; i<cities.length; ++i) {
            String key = cities[i].toLowerCase();
            
            if(cache.get(key) == null) {
                answer += 5;
                
                if(cache.size() < cacheSize) {
                    cache.put(key, i);
                } else {
                    String oldestKey = findOldestKey(cache);
                    cache.remove(oldestKey);
                    cache.put(key, i);
                }
            } else {
                answer++;
                cache.replace(key, i);
            }
        }
        return answer;
    }
    
    private String findOldestKey(Map<String, Integer> cache) {
        String oldestKey = "";
        int oldestValue = MAX; 
        
        for(String key : cache.keySet()) {
            int value = cache.get(key);
            if(value < oldestValue) {
                oldestKey = key;
                oldestValue = value;
            }
        }
        return oldestKey;
    }
}
