import java.util.*;

class Solution {
    public int[] solution(String[] operations) {
        
        PriorityQueue<Integer> minHeap = new PriorityQueue<>();
        PriorityQueue<Integer> maxHeap = new PriorityQueue<>(Collections.reverseOrder());
        Map<Integer, Integer> map = new HashMap<>();
        char cmd;
        int num;
        
        for(String op : operations) {
            cmd = op.charAt(0);
            num = Integer.parseInt(op.substring(2));
            
            if(cmd == 'I') {
                minHeap.add(num);
                maxHeap.add(num);
                map.put(num, map.getOrDefault(num, 0) + 1);
            } else {
                if(num > 0) {
                    while(!maxHeap.isEmpty()) {
                        int top = maxHeap.poll();
                        if(map.get(top) != 0) {
                            map.put(top, map.get(top) - 1);
                            break;
                        } 
                    }
                } else {
                    while(!minHeap.isEmpty()) {
                        int top = minHeap.poll();
                        if(map.get(top) != 0) {
                            map.put(top, map.get(top) -  1);
                            break;
                        }
                    }
                }
            }
        }
        
        return getAnswer(minHeap, maxHeap, map);
    }
    
    int[] getAnswer(Queue<Integer> minHeap, Queue<Integer> maxHeap, Map<Integer, Integer> map) {
        int maxVal = 0;
        int minVal = 0;
        int top;
        while(!maxHeap.isEmpty()) {
            top = maxHeap.poll();
            if(map.get(top) != 0) {
                maxVal = top;
                break;
            }
        }
        while(!minHeap.isEmpty()) {
            top = minHeap.poll();
            if(map.get(top) != 0) {
                minVal = top;
                break;
            }
        }
        return new int[] {maxVal, minVal};
    }
}
