class Solution {
    
    int[] answer = new int[11];
    int maxScoreDiff = 0; 
    
    public int[] solution(int n, int[] info) {
        
        int[] lionInfo = new int[11];
        getLionInfo(info, lionInfo, 0, n);
        
        if(maxScoreDiff == 0) {
            return new int[] {-1};
        }
        return answer;
    }
    
    void getLionInfo(int[] info, int[] lionInfo, int idx, int n) {
        //base case
        if(n == 0) {
            //점수차 계산하기
            int scoreDiff = calScore(info, lionInfo);
            if(scoreDiff > 0) {
                if(scoreDiff > maxScoreDiff) {
                    maxScoreDiff = scoreDiff;
                    updateAnswer(lionInfo);
                } else if(scoreDiff == maxScoreDiff) {
                    if(isUpdate(lionInfo)) {
                        updateAnswer(lionInfo);
                    }
                }
            }
            return;
        }
        
        //가능한 점수 조합 구하기
        for(int i = idx; i < 11; ++i) {
            if(i < 10) {
                if(info[i] < n) {
                    lionInfo[i] = info[i] + 1;
                    getLionInfo(info, lionInfo, i + 1, n - (info[i] + 1));
                    lionInfo[i] = 0;
                }
            } else {
                lionInfo[i] = n;
                getLionInfo(info, lionInfo, i + 1, n - lionInfo[i]);
                lionInfo[i] = 0;
            }
        }
    }
    
    int calScore(int[] info, int[] lionInfo) {
        int apache = 0;
        int lion = 0;
        for(int i = 0; i < 11; ++i) {
            if(info[i] == 0 && lionInfo[i] == 0) {
                continue;
            }
            
            if(info[i] < lionInfo[i]) {
                lion += (10 - i);
            } else {
                apache += (10 - i);
            }
        }
        return lion - apache;
    }
    
    void updateAnswer(int[] lionInfo) {
        for(int i = 0; i < 11; ++i) {
            answer[i] = lionInfo[i];
        }
    }
    
    boolean isUpdate(int[] lionInfo) {
        for(int i = 10; i >= 0; --i) {
            if(lionInfo[i] > answer[i]) {
                return true;
            } else if(lionInfo[i] < answer[i]) {
                return false;
            }
        }
        return false;
    }
}
