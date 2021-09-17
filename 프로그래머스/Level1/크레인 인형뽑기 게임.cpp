#include <string>
#include <vector>

using namespace std;

int solution(vector<vector<int>> board, vector<int> moves) {
    int answer = 0;
    
    int board_size = board[0].size();
    int doll;
    vector<int> bucket;
    for(int i=0; i<moves.size(); ++i){
        int crain = moves[i] - 1;
        doll = 0;
        for(int j=0; j<board_size; ++j){
            if(board[j][crain] == 0)
                continue;
            else{
                doll = board[j][crain];
                board[j][crain] = 0;
                break;
            }
        }
        if(doll == 0)
            continue;
        else{
            
            if(!bucket.empty() && bucket.back() == doll){
                answer += 2;
                bucket.pop_back();
            }
            else
                bucket.push_back(doll);
        }
    }
    return answer;
}
