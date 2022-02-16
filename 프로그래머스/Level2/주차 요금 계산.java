import java.util.*;

class Solution {
    
    private final int MAX_TIME = 23 * 60 + 59;
    
    public int[] solution(int[] fees, String[] records) {
        
        Map<String, Integer> totalTimes = caltotalTime(records);
        
        int[] answer = calTotalCost(fees, totalTimes);
        
        return answer;
    }
    
    Map<String, Integer> caltotalTime(String[] records) {
        
        Map<String, Integer> totalTimes = new TreeMap<>();
        for(String record : records) {
            //parsing record
            String[] info = record.split(" ");
            
            int time = (info[2].equals("IN"))? -1 : 1;
            time *= getTime(info[0]);
            
            totalTimes.put(info[1], totalTimes.getOrDefault(info[1], 0) + time);
        }
        
        return totalTimes;
    }
    
    int getTime(String time) {
        String[] tmp = time.split(":");
        return Integer.parseInt(tmp[0]) * 60 + Integer.parseInt(tmp[1]);
    }
    
    int[] calTotalCost(int[] fees, Map<String, Integer> totalTimes) {
        int[] costs = new int[totalTimes.size()];
        int idx = 0;
        
        for(Map.Entry<String, Integer> entry : totalTimes.entrySet()) {
            int totalTime = entry.getValue();
            if(totalTime <= 0) { //아직 출차한 기록이 없는 경우
                totalTime += MAX_TIME;                
            } 
            
            int cost = fees[1];
            totalTime -= fees[0];
            
            if(totalTime > 0) {
                int extraCost = (totalTime % fees[2] == 0)? (totalTime / fees[2]) : (totalTime / fees[2] + 1);
                cost += (extraCost * fees[3]); 
            }
            costs[idx++] = cost;
        }
        
        return costs;
    }   
    
}
