class Solution {
    public String solution(String play_time, String adv_time, String[] logs) {
        
        //비디오 누적 재생 횟수 구하기
        int[] playCntRecord = getPlayCntRecord(play_time, logs);
        
        //광고 삽입 시간 구하기
        int advStartTime = 0;
        int advTime = convertTime(adv_time);
        long maxWatchTime = 0;
        for (int i = advStartTime; i < advTime; ++i) {
            maxWatchTime += playCntRecord[i];
        }
        
        long watchTime = maxWatchTime;
        for (int i = 1; i + advTime <= convertTime(play_time); ++i) {
            watchTime -= playCntRecord[i - 1];
            watchTime += playCntRecord[i + advTime - 1];
            
            if (watchTime > maxWatchTime) {
                advStartTime = i;
                maxWatchTime = watchTime;
            }
        }
        
        return convertTime(advStartTime);
    }
    
    private int[] getPlayCntRecord(String playTime, String[] records) {
        
        int[] playCntRecord = new int[convertTime(playTime) + 1];
        
        for (String record : records) {
            String[] times = record.split("-");
            int startTime = convertTime(times[0]);
            int endTime = convertTime(times[1]);
            
            playCntRecord[startTime]++;
            playCntRecord[endTime]--;
        }
        
        for (int i = 1; i < playCntRecord.length; ++i) {
            playCntRecord[i] += playCntRecord[i - 1];
        }
        
        return playCntRecord;
    }
    
    private int convertTime(String time) {
        String[] tokens = time.split(":");
        
        int intTime = Integer.valueOf(tokens[2]);
        intTime += Integer.valueOf(tokens[1]) * 60;
        intTime += Integer.valueOf(tokens[0]) * 60 * 60;
        
        return intTime;
    }
    
    private String convertTime(int time) {
        StringBuilder stringTime = new StringBuilder();
        
        stringTime.append(String.format("%02d:", time / (60 * 60)));
        
        time = time % (60 * 60);
        stringTime.append(String.format("%02d:", time / 60));
        
        time = time % 60;
        stringTime.append(String.format("%02d", time));
        
        return stringTime.toString();
    }
}
