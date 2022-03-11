class Solution {
    
    public String solution(String play_time, String adv_time, String[] logs) {
        
        int playTime = convertTime(play_time);
        int[] video = new int[playTime + 1];
        
        //log를 이용해 video에 해당 시간에 시청자 시청자 수 기록
        for(String log : logs) {
            String[] times = log.split("-");
            int startT = convertTime(times[0]);
            int endT = convertTime(times[1]);
            
            for(int i = startT; i < endT; ++i) {
                video[i] += 1;
            }
        }
        
        //video 이용해 광고가 들어갈 위치 찾기
        int advT = convertTime(adv_time);
        int advStartT = 0;
        long playSum = 0;
        for(int i = 0; i < advT; ++i) {
            playSum += video[i];
        }
        
        long maxPlaySum = playSum;
        for(int i = advStartT + 1; i <= playTime - advT; ++i) {
            playSum -= video[i - 1];
            playSum += video[i + advT - 1];
            
            if(playSum > maxPlaySum) {
                maxPlaySum = playSum;
                advStartT = i;
            }
        }
        
        String answer = String.format("%02d:%02d:%02d", advStartT / 3600, (advStartT % 3600) / 60, (advStartT % 60)); 
        return answer;
    }
    
    int convertTime(String time) {
        String[] token = time.split(":");
        
        int convertTime = Integer.parseInt(token[0]) * 3600;
        convertTime += Integer.parseInt(token[1]) * 60;
        convertTime += Integer.parseInt(token[2]);
        return convertTime;
    }
    
}

//최적화 풀이
