import java.util.*;

class Solution {
    public int solution(int[] people, int limit) {
        
        Arrays.sort(people);
        
        int boatCnt = 0;
        int lightest = 0;
        int heaviest = people.length - 1;
        while (lightest <= heaviest) {
            if (people[lightest] + people[heaviest] <= limit) {
                lightest++;
                heaviest--;
            } else {
                heaviest--;
            }
            boatCnt++;
        }
        
        return boatCnt;
    }
}

/* O(241) 풀이 (몸무게 범위) */
class Solution {
    public int solution(int[] people, int limit) {
        
        int[] weights = new int[241];
        for (int weight : people) {
            weights[weight]++;
        }
        
        int answer = 0;
        
        /* 무조건 혼자 타야하는 사람 */
        for (int i = limit; i > limit - 40; --i) {
            answer += weights[i];
            weights[i] = 0;
        }
        
        /* 같이 탈 수 있으면 같이타고, 불가능하면 혼자 타기 */
        int light = 40;
        int heavy = limit - 40;
        while (light < heavy) {
            if (weights[light] == 0) {
                light++;
                continue;
            }
            
            if (weights[heavy] == 0) {
                heavy--;
                continue;
            }
            
            if (light + heavy > limit) {
                answer += weights[heavy];
                
                weights[heavy] = 0;
                
                heavy--;
                continue;
            }
            
            if (weights[light] > weights[heavy]) {
                answer += weights[heavy];
                
                weights[light] -= weights[heavy];
                weights[heavy] = 0;
                
                heavy--;
            } else if (weights[light] < weights[heavy]){
                answer += weights[light];
                
                weights[heavy] -= weights[light];
                weights[light] = 0;
                
                light++;
            } else {
                answer += weights[light];
            
                weights[light] = 0;
                weights[heavy] = 0;
                
                light++;
                heavy--;
            }
        }
        
        if (light == heavy) {
            if (light * 2 > limit) {
                answer += weights[light];
            } else {
                answer += (int)Math.ceil((double)weights[light] / 2);
            }
        }
        
        return answer;
    }
}
