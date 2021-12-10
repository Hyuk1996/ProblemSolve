#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <queue>

using namespace std;


// 전역 변수를 정의할 경우 함수 내에 초기화 코드를 꼭 작성해주세요.

bool checkPossible(vector<string>& board, int startY, int startX, int endY, int endX) {
    
    // BFS 이용해 제거 가능한 타일인지 확인하기.
    int dy[4] = {0, 0, -1, 1};
    int dx[4] = {-1, 1, 0, 0};
    vector<vector<int>> check(board.size(),vector<int>(board[0].size(), 3)); // check[y][x]: 출발점에서 y,x까지 가는데 꺾은 경로 횟수 저장.
    queue<pair<pair<int, int>, pair<int, int>>> q; // (y좌표, x좌표, 현재 진행 방향, 바뀐 진행 방향 수)
    
    q.push(make_pair(make_pair(startY, startX), make_pair(-1, -1)));
    check[startY][startX] = 0;
    while(!q.empty()) {
        int curY = q.front().first.first;
        int curX = q.front().first.second;
        int curDir = q.front().second.first;
        int changeDirCnt = q.front().second.second;
        q.pop();
        
        if(curY == endY && curX == endX)
            return true;
        
        for(int i=0; i<4; ++i) {
            int nextY = curY + dy[i];
            int nextX = curX + dx[i];
            int nextDir = i;
            int nextChangeDirCnt= changeDirCnt;
            
            // 범위 체크.
            if(nextY < 0 || nextY >= board.size() || nextX < 0 || nextX >= board[curY].size())
                continue;
            // 전진 가능여부 확인
            if(board[nextY][nextX] != '.' && board[nextY][nextX] != board[startY][startX])
                continue;
            
            if(nextDir != curDir)
                ++nextChangeDirCnt;
            
            if(nextChangeDirCnt >= 2)
                continue;
            
            if(check[nextY][nextX] >= nextChangeDirCnt) {
                check[nextY][nextX] = nextChangeDirCnt;
                q.push(make_pair(make_pair(nextY, nextX), make_pair(nextDir, nextChangeDirCnt)));
            }
        }
    }
    return false;
}
string solution(int m, int n, vector<string> board) {
    
    // board의 타일 정보 Map 이용해 저장.
    map<char, vector<pair<int, int>>> tileDict;
    for(int i=0; i<m; ++i) {
        for(int j=0; j<n; ++j) {
            if('A' <= board[i][j] && board[i][j] <= 'Z') {
                tileDict[board[i][j]].push_back(make_pair(i, j));
            }
        }
    }
    

    // 게임 시작. Map의 특성상 알파벳 순으로 정렬되어 있다. 
    string answer = "";
    bool gameFinish;
    while(true) {
        gameFinish = true;
        
        for(auto it = tileDict.begin(); it != tileDict.end(); ++it) {
            
            char tile = it->first;
            int startY = it->second[0].first;
            int startX = it->second[0].second;
            int endY = it->second[1].first;
            int endX = it->second[1].second;
            if(checkPossible(board, startY, startX, endY, endX)) {
                answer += tile;
                board[startY][startX] = '.';
                board[endY][endX] = '.';
                tileDict.erase(it);
                gameFinish = false;
                break;
            }
        }        
        
        if(gameFinish)
            break;
    }
    
    
    if(tileDict.empty())
        return answer;
    else
        return "IMPOSSIBLE";
}
