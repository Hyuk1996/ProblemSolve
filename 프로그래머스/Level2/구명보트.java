import java.util.*;

class Solution {
    public int solution(int[] people, int limit) {
        
        Arrays.sort(people);
        
        int boatCnt = 0;
        int lightest = 0;
        int heaviest = people.length - 1;
        while (lightest < heaviest) {
            if (people[lightest] + people[heaviest] <= limit) {
                lightest++;
                heaviest--;
            } else {
                heaviest--;
            }
            boatCnt++;
        }
        
        if (lightest == heaviest) {
            boatCnt++;
        }
        
        return boatCnt;
    }
}
