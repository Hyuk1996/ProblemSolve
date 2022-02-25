import java.util.*;

class Solution {
    
    private final int START_TIME = 9 * 60;
    
    public String solution(int n, int t, int m, String[] timetable) {
      
        PriorityQueue<Integer> waitLine = sortTimetable(timetable);
        int boardCrewCnt = 0;
        int lastBoardTime = 0;
        int busArrivedTime = START_TIME - t;
        
        //n개의 버스에 탑승 시작
        for(int i = 0; i < n; ++i) {
            boardCrewCnt = 0;
            lastBoardTime = 0;
            busArrivedTime += t;
            
            while(boardCrewCnt < m && !waitLine.isEmpty()) {
                int crewArrivedTime = waitLine.peek();
                if(crewArrivedTime > busArrivedTime) {
                    break;
                }
                
                boardCrewCnt++;
                lastBoardTime = crewArrivedTime;
                waitLine.remove();
            }
        }
        
        //마지막 버스를 탑승한 승객 정보를 이용해 콘의 도착 시간 구하기
        int conArrivedTime = (boardCrewCnt == m)? lastBoardTime - 1 : busArrivedTime;
        return String.format("%02d:%02d", conArrivedTime / 60, conArrivedTime % 60);
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
    
}
