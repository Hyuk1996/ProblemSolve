import java.util.*;

class Solution {
    public int solution(int N, int number) {
        
        //nums[i] 는 N을 i개 이용해 만들 수 있는 숫자들의 집합.
        List<Set<Integer>> nums = new ArrayList<>();
        for(int i = 0; i <= 8; ++i) {
            nums.add(new HashSet());
        }
        
        nums.get(1).add(N);
        
        for(int i = 2; i <= 8; ++i) {
            for(int j = 1; j < i; ++j) {
                Set<Integer> preNums = nums.get(j);
                Set<Integer> postNums = nums.get(i - j);
                
                for(int preNum : preNums) {
                    for(int postNum : postNums ) {
                        nums.get(i).add(preNum + postNum);
                        nums.get(i).add(preNum - postNum);
                        nums.get(i).add(preNum * postNum);
                        if(postNum != 0) {
                            nums.get(i).add(preNum / postNum);
                        }
                    }
                }
            }
            nums.get(i).add(Integer.parseInt(String.valueOf(N).repeat(i)));
        }
        
        //nums list에서 문제 입력 numbers가 존재하는지 확인
        int answer = -1;                    
        for(int i = 1; i <= 8; ++i) {
            if(nums.get(i).contains(number)) {
                answer = i;
                break;
            }
        }
                            
        return answer;
    }
}
