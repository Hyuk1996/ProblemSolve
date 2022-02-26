import java.util.*;

class Solution {
    
    private int[] IDT;
    
    public String solution(int n, int k, String[] cmd) {
        String answer = "";
        
        makeIDT(n);
        Stack<Integer> delete = new Stack<>();
        
        int x;
        for(String c : cmd) {
            String[] token = c.split(" ");
            
            if(token[0].equals("U")) {
                
                x = Integer.parseInt(token[1]);
                k = upBinarySearch(k - 1, x);
                
            } else if(token[0].equals("D")) {
                
                x = Integer.parseInt(token[1]);
                k = downBinarySearch(k + 1, x, n);
                
            } else if(token[0].equals("C")) {
                
                delete.push(k);
                updateIDT(k, 0);
                
                int nextK = downBinarySearch(k + 1, 1, n);
                if(rangeSum(k + 1, nextK) != 1) {
                    nextK = upBinarySearch(k - 1, 1);
                }
                k = nextK;
                
            } else {
                
                int deleteIdx = delete.pop();
                updateIDT(deleteIdx, 1);
            }
            
        }
        
        answer = compare(n);
        return answer;
    }
    
    private void makeIDT(int n) {
        int leafSize = 1;
        while(leafSize < n) {
            leafSize *= 2;
        }
        
        IDT = new int[leafSize * 2];
        
        //leaf node 초기화
        for(int i = 0; i < n; ++i) {
            IDT[i + leafSize] = 1;
        }
        
        //internal node 초기화
        for(int i = leafSize - 1; i > 0; --i) {
            IDT[i] = IDT[i * 2] + IDT[i * 2 + 1];
        }
    }
    
    private int upBinarySearch(int right, int x) {
        int lo = 0;
        int hi = right + 1;
        while(lo + 1 < hi) {
            int mid = lo + (hi - lo) / 2;
            if(rangeSum(mid, right) >= x) {
                lo = mid;
            } else {
                hi = mid;
            }
        }
        return lo;
    }
    
    private int downBinarySearch(int left, int x, int n) {
        int lo = left - 1;
        int hi = n - 1;
        while(lo + 1 < hi) {
            int mid = lo + (hi - lo) / 2;
            if(rangeSum(left, mid) < x) {
                lo = mid;
            } else {
                hi = mid;
            }
        }
        return hi;
    }
    
    private int rangeSum(int left, int right) {
        left += IDT.length / 2;
        right += IDT.length / 2;
        int sum = 0;
        
        while(left <= right) {
            if(left % 2 == 1) {
                sum += IDT[left];   
            }
            if(right % 2 == 0) {
                sum += IDT[right];
            }
            
            left = (left + 1) / 2;
            right = (right - 1) / 2;
        }
        return sum;
    }
    
    private void updateIDT(int p, int val) {
        p += IDT.length / 2;
        IDT[p] = val;
        while(p > 1) {
            p /= 2;
            IDT[p] = IDT[p * 2] + IDT[p * 2 + 1];
        }
    }
    
    private String compare(int n) {
        StringBuilder sb = new StringBuilder();
        
        int start = IDT.length / 2;
        for(int i = 0; i < n; ++i) {
            if(IDT[i + start] == 1) {
                sb.append("O");
            } else {
                sb.append("X");
            }
        }
        return sb.toString();
    }
    
}

//더블링크드리스트 풀이
import java.util.*;

class Solution {
    
    private Node cursor;
    
    public String solution(int n, int k, String[] cmd) {
        
        initList(n, k);
        Stack<Node> deleteNode = new Stack<>();
        
        for(String query : cmd) {
            String[] token = query.split(" ");
            
            if(token[0].equals("U")) {
                int x = Integer.parseInt(token[1]);
                for(int i = 0; i < x; ++i) {
                    cursor = cursor.prev;
                }
            } else if(token[0].equals("D")) {
                int x = Integer.parseInt(token[1]);
                for(int i = 0; i < x; ++i) {
                    cursor = cursor.next;
                }
            } else if(token[0].equals("C")) {
                
                Node nextCursor = (cursor.next != null)? cursor.next : cursor.prev;
                
                cursor.remove();
                deleteNode.push(cursor);
                
                cursor = nextCursor;
            } else {
                deleteNode.pop().restore();
            }
        }
        
        String answer = compare(n, deleteNode);
        return answer;
    }
    
    void initList(int n, int k) {
        Node tail = new Node(0);
        if(k == 0) {
            cursor = tail;
        }
        for(int i = 1; i < n; ++i) {
            Node cur = new Node(i);
            if(k == i) {
                cursor = cur;
            }
            
            //이어주기
            tail.next = cur;
            cur.prev = tail;
            
            tail = cur;
        }
    }
    
    String compare(int n, Stack<Node> deleteNode) {
        StringBuilder sb = new StringBuilder();
        for(int i = 0; i < n; ++i) {
            sb.append("O");
        }
        while(!deleteNode.isEmpty()) {
            sb.setCharAt(deleteNode.pop().idx, 'X');
        }
        return sb.toString();
    }
    
    class Node {
        int idx;
        Node next = null;
        Node prev = null;
        
        Node(int idx) {
            this.idx = idx;
        }
        
        void remove() {
            if(prev != null) {
                prev.next = next;
            }
            if(next != null) {
                next.prev = prev;
            }
        }
        
        void restore() {
            if(prev != null) {
                prev.next = this;
            }
            if(next != null) {
                next.prev = this;
            }
        }
    }
}
