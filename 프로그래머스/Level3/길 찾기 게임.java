import java.util.*;

class Solution {
    
    Node[] nodes;
    int idx;
    
    public int[][] solution(int[][] nodeinfo) {
        
        makeBinaryTree(nodeinfo);
        
        int[][] answer = new int[2][nodes.length];
        
        idx = 0;
        preorder(nodes[0], answer[0]);
        
        idx = 0;
        postorder(nodes[0], answer[1]);
        
        return answer;
    }
    
    void makeBinaryTree(int[][] nodeinfo) {
        //초기작업
        nodes = new Node[nodeinfo.length];
        for(int i = 0; i < nodeinfo.length; ++i) {
            nodes[i] = new Node(nodeinfo[i][0], nodeinfo[i][1], i + 1);
        }
        
        //y좌표 내림차순 정렬
        Arrays.sort(nodes, new Comparator<Node>() {
            @Override
            public int compare(Node n1, Node n2) {
                return n2.y - n1.y;
            }
        });
        
        Node root = nodes[0];
        //Node 삽입
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
    
    void preorder(Node node, int[] answer) {
        answer[idx++] = node.value;
        if(node.left != null) {
            preorder(node.left, answer);
        }
        if(node.right != null) {
            preorder(node.right, answer);
        }
    }
    
    void postorder(Node node, int[] answer) {
        if(node.left != null) {
            postorder(node.left, answer);
        }
        if(node.right != null) {
            postorder(node.right, answer);
        }
        answer[idx++] = node.value;
    }
    
    class Node {
        int x;
        int y;
        int value;
        Node left = null;
        Node right = null;
        
        Node(int x, int y, int value) {
            this.x = x;
            this.y = y;
            this.value = value;
        }
    }
}
