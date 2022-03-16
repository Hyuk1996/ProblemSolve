import java.util.*;

class Solution {
    
    Node[] nodes;
    
    public int[][] solution(int[][] nodeinfo) {
        
        makeBinaryTree(nodeinfo);
        
        Queue<Integer> preorders = new LinkedList<>();
        preorder(nodes[0], preorders);
        
        Queue<Integer> postorders = new LinkedList<>();
        postorder(nodes[0], postorders);
        
        return getAnswer(preorders, postorders);
    }
    
    void makeBinaryTree(int[][] nodeinfo) {
        nodes = new Node[nodeinfo.length];
        for(int i = 0; i < nodeinfo.length; ++i) {
            nodes[i] = new Node(nodeinfo[i][0], nodeinfo[i][1], i + 1);
        }
        
        Arrays.sort(nodes, new Comparator<Node>() {
            @Override
            public int compare(Node o1, Node o2) {
                return o2.y - o1.y;
            }
        });
        
        Node root = nodes[0];
        for(int i = 1; i < nodes.length; ++i) {
            insertNode(root, nodes[i]);
        }
    }
    
    void insertNode(Node parent, Node node) {
        if(parent.x > node.x) {
            if(parent.left == null) {
                parent.left = node;
                return;
            }
            insertNode(parent.left, node);
        } else {
            if(parent.right == null) {
                parent.right = node;
                return;
            }
            insertNode(parent.right, node);
        }
    }
    
    void preorder(Node node, Queue<Integer> preorders) {
        preorders.add(node.no);
        if(node.left != null) {
            preorder(node.left, preorders);
        }
        if(node.right != null) {
            preorder(node.right, preorders);
        }
    }
    
    void postorder(Node node, Queue<Integer> postorders) {
        if(node.left != null) {
            postorder(node.left, postorders);
        }
        if(node.right != null) {
            postorder(node.right, postorders);
        }
        postorders.add(node.no);
    }
    
    int[][] getAnswer(Queue<Integer> preorders, Queue<Integer> postorders) {
        int[][] answer = new int[2][preorders.size()];
        
        int idx = 0;
        while(!preorders.isEmpty()) {
            answer[0][idx++] = preorders.poll();
        }
        
        idx = 0;
        while(!postorders.isEmpty()) {
            answer[1][idx++] = postorders.poll();
        }
        
        return answer;
    }
    
    class Node {
        int x;
        int y;
        int no;
        Node left;
        Node right;
        
        Node(int x, int y, int no) {
            this.x = x;
            this.y = y;
            this.no = no;
        }
    }
}
