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

/* 직관적인 풀이 */
import java.util.*;

class Solution {
    
    private List<List<Integer>> scoreCombies = new ArrayList<>();
    
    public int[] solution(int n, int[] info) {
        
        //라이언이 얻을 수 있는 모든 점수 조합 구하기
        for (int i = 1; i <= n; ++i) {
            List<Integer> combie = new ArrayList<>();
            getCombi(combie, 0, i);
        }
        
        //정답 구하기
        int maxDiff = 0;
        boolean isAnswer = false;
        int[] answer = new int[11];
        for (List<Integer> combi : scoreCombies) {
                
            //만들 수 있는 점수 조합인지 확인하기
            if (!isPossibleCombie(combi, info, n)) {
                continue;
            }
            
            int[] lionInfo = throwArrow(combi, info, n);
            
            //점수 차 구하기
            int scoreDiff = getScoreDiff(info, lionInfo);
            
            if (maxDiff < scoreDiff) {
                maxDiff = scoreDiff;
                
                isAnswer = true;
                for (int i = 0; i < 11; ++i) {
                    answer[i] = lionInfo[i];
                }
            } else if (maxDiff == scoreDiff) {
                if (isNewAnswer(answer, lionInfo)) {
                    for (int i = 0; i < 11; ++i) {
                        answer[i] = lionInfo[i];
                    }
                }
            }
        }
        
        if (!isAnswer) {
            return new int[]{-1};
        }
        return answer;
    }
    
    private boolean isPossibleCombie(List<Integer> combie, int[] info, int n) {
        int arrowCnt = 0;
        
        for (Integer score : combie) {
            arrowCnt += info[10 - score] + 1;
        }
        
        return arrowCnt <= n;
    }
    
    private int[] throwArrow(List<Integer> combie, int[] info, int n) {
        
        int[] lionInfo = new int[info.length];
        for (Integer score : combie) {
            int apeachArrowCnt = info[10 - score];
            lionInfo[10 - score] = apeachArrowCnt + 1;
            n -= apeachArrowCnt + 1;
        }
        
        //남은 화살은 가장 낮은 점수 쏘기
        lionInfo[10] += n;
        
        return lionInfo;
    }
    
    private int getScoreDiff(int[] apeach, int[] lion) {
        int lionScore = 0;
        int apeachScore = 0;
        for (int i = 0; i < 11; ++i) {
            if (apeach[i] == 0 && lion[i] == 0) {
                continue;
            }
                
            if (apeach[i] >= lion[i]) {
                apeachScore += 10 - i;
            } else {
                lionScore += 10 - i;
            }
        }
        return lionScore - apeachScore;
    }
    
    private boolean isNewAnswer(int[] answer, int[] lionInfo) {
        for (int i = 10; i >= 0; --i) {
            if (answer[i] < lionInfo[i]) {
                return true;
            }
        }
        return false;
    }
    
    private void getCombi(List<Integer> combie, int idx, int n) {
        if (combie.size() == n) {
            scoreCombies.add(new ArrayList<>(combie));
            return;
        }
        
        for (int i = idx; i <= 10; ++i) {
            combie.add(10 - i);
            getCombi(combie, i + 1, n);
            combie.remove(combie.size() - 1);
        }
    }
}
