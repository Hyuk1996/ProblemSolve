import java.util.ArrayList;
import java.lang.Math;

class Solution {
    private int answer = -1;
    
    
    public int solution(int k, int[][] dungeons) {

        boolean[] isVisited = new boolean[dungeons.length];
        ArrayList<Integer> order = new ArrayList<>();
        
        getPermutation(dungeons, order, k, isVisited);
        
        return answer;
    }
    
    private void getPermutation(int[][] dungeons, ArrayList<Integer> order, int k, boolean[] isVisited) {
        if(order.size() == dungeons.length) {
            answer = Math.max(answer, getAnswer(dungeons, order, k));
            return;
        }
        for(int i=0; i<dungeons.length; ++i) {
            if(!isVisited[i]) {
                isVisited[i] = true;
                order.add(i);
                getPermutation(dungeons, order, k, isVisited);
                int idx = order.size();
                order.remove(idx - 1);
                isVisited[i] = false;
            }
        }
    }
    
    private int getAnswer(int[][] dungeons, ArrayList<Integer> order, int k) {
        int dungeonsCnt = 0;
        for(int i=0; i<order.size(); ++i) {
            if(dungeons[order.get(i)][0] > k) {
                break;
            }
            k -= dungeons[order.get(i)][1];
            dungeonsCnt++;
        }
        return dungeonsCnt;
    }
}
