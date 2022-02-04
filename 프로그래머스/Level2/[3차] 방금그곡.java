import java.util.*;

class Solution {
    public String solution(String m, String[] musicinfos) {
        
        //C# -> c, D# -> d, F# -> f, G# -> g, A# -> a
        m = replaceStr(m);
        
        String answer = "(None)";
        int answerTime = 0;
        for(String musicInfo : musicinfos) {
            String[] infos = musicInfo.split(",");
            
            int playTime = getPlayTime(infos[0], infos[1]);
            
            if(playTime > answerTime) {
                if(check(m, infos[3], playTime)) {
                    answer = infos[2];
                    answerTime = playTime;
                }
            }
        }
        
        return answer;
    }
    
    private int getPlayTime(String start, String end) {
        
        int startT = (Integer.parseInt(start.substring(0, 2))) * 60 + Integer.parseInt(start.substring(3));
        int endT = (Integer.parseInt(end.substring(0, 2))) * 60 + Integer.parseInt(end.substring(3));
        
        return endT - startT;
    }
    
    private boolean check(String m, String melody, int playTime) {
        melody = replaceStr(melody);
        
        //재생시간에 맞게 멜로디 정보 수정
        melody = changeMelody(melody, playTime);
        
        return melody.contains(m);
    }
    
    //C# -> c, D# -> d, F# -> f, G# -> g, A# -> a
    private String replaceStr(String str) {
        return str.replace("C#", "c")
            .replace("D#", "d")
            .replace("F#", "f")
            .replace("G#", "g")
            .replace("A#", "a");
    }
    
    private String changeMelody(String melody, int playTime) {
        StringBuilder sb = new StringBuilder();
        
        if(melody.length() > playTime) {
            sb.append(melody.substring(0, playTime));
        } else {
            int tmpCnt = playTime / melody.length();
            int tmp = playTime % melody.length();
            
            for(int i = 0; i < tmpCnt; ++i) {
                sb.append(melody);
            }
            sb.append(melody.substring(0, tmp));
        }
        
        return sb.toString();
    }
    
}
