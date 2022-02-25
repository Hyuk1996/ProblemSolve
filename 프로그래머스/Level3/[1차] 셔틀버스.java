import java.util.*;

class Solution {
    
    private final int START_TIME = 9 * 60;
    
    public String solution(int n, int t, int m, String[] timetable) {
      
        PriorityQueue<Integer> waitLine = sortTimetable(timetable);
        List<Integer> bus = new ArrayList<>();
        
        //탑승 시작
        for(int i = 0; i < n; ++i) {
            bus.clear();
            
            int arrivedTime = START_TIME + (t * i);
            
            while(bus.size() < m && !waitLine.isEmpty()) {
                int crewTime = waitLine.peek();
                if(crewTime > arrivedTime) {
                    break;
                }
                
                bus.add(crewTime);
                waitLine.remove();
            }
        }
        
        //마지막 버스를 탑승한 승객 정보를 이용해 콘의 도착 시간 구하기
        int conArriveTime = (bus.size() == m)? bus.get(m - 1) - 1 : START_TIME + (t * (n - 1));
        
        String answer = makeAnswerFormat(conArriveTime);
        return answer;
    }
    
    private PriorityQueue<Integer> sortTimetable(String[] timetable) {
        PriorityQueue<Integer> waitLine = new PriorityQueue<>();
        for(int i = 0; i < timetable.length; ++i) {
            waitLine.add(convertTime(timetable[i]));
        }
        return waitLine;
    }
    
    public Integer convertTime(String time) {
        String[] tmp = time.split(":");
        return Integer.parseInt(tmp[0]) * 60 + Integer.parseInt(tmp[1]);
    }
    
    private String makeAnswerFormat(int conTime) {
        String time = (conTime / 60 < 10)? "0" : "";
        time += String.valueOf(conTime / 60) + ":";
        time += (conTime % 60 < 10)? "0" : "";
        time += String.valueOf(conTime % 60);
        return time;
    }
}
