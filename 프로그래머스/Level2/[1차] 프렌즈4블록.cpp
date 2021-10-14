#include <string>
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

int solution(int m, int n, vector<string> board) {
    int answer = 0;
    
    vector<vector<bool>> visit(m, vector<bool>(n, 0));
    
    while(true){
        int erase_blocks = 0;
        for(int i=0; i<m; i++){
            for(int j=0; j<n; j++){
                // 근처 2x2 모양이 있는지 확인.
                if(j+1 < n && i+1 < m && board[i][j] != ' '){
                    bool flag = true;
                    if(board[i][j] != board[i][j+1])
                        flag = false;
                    if(board[i][j] != board[i+1][j])
                        flag = false;
                    if(board[i][j] != board[i+1][j+1])
                        flag = false;
                    
                    if(flag){
                        for(int x=i; x<=i+1; x++){
                            for(int y=j; y<=j+1; y++){
                                if(!visit[x][y]){
                                    visit[x][y] = true;
                                    erase_blocks++;
                                }
                            }
                        }
                    }
                }
            }
        }
        
        if(erase_blocks == 0) // 더 이상 2 x 2 block이 없으면 loop 종료.
            break;
        else{ // 2 x 2 block이 있었으면 해당 블록들 지워진 것을 board에 반영.
            answer += erase_blocks;
            
            for(int i=0; i<n; i++){
                queue<char> q;
                for(int j=m-1; j>=0; j--){
                    if(!visit[j][i])
                        q.push(board[j][i]);
                    else
                        visit[j][i] = false;
                }
                
                for(int j=m-1; j>=0; j--){
                    if(q.empty())
                        board[j][i] = ' ';
                    else{
                        board[j][i] = q.front();
                        q.pop();
                    }
                }
            }
        }
    }
    
    return answer;
}
