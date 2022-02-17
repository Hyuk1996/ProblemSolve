class Solution {
    public String solution(String s) {
        
        String[] nums = s.split(" ");
        int min = Integer.parseInt(nums[0]);
        int max = min;
        int num;
        for(int i = 1; i < nums.length; ++i) {
            num = Integer.parseInt(nums[i]);
            min = Math.min(min, num);
            max = Math.max(max, num);
        }
        
        String answer = min + " " + max;
        return answer;
    }
}
