#include <string>
#include <vector>
#include <cstdlib>

using namespace std;

struct pos{
    int x;
    int y;
};

string solution(vector<int> numbers, string hand) {
    string answer = "";
    char keypad[4][3] = {{'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}, {'*', '0', '#'}};
    
    pos curr_R{2, 3};
    pos curr_L{0, 3};
    char push_hand;
    for(int i=0; i<numbers.size(); ++i){
        if((numbers[i] % 3) == 1){
            curr_L.x = 0;
            curr_L.y = numbers[i] / 3;
            push_hand = 'L';
        }
        else if(numbers[i] != 0 && numbers[i] % 3 == 0){
            curr_R.x = 2;
            curr_R.y = (numbers[i] / 3) - 1;
            push_hand = 'R';
        }
        else{
            pos number_pos;
            for(int k=0; k<4; ++k)
                for(int j=0; j<3; ++j)
                    if(numbers[i] == (keypad[k][j] - '0')){
                        number_pos.x = j;
                        number_pos.y = k;
                        break;
                    }
            int dist_L = abs(curr_L.x - number_pos.x) + abs(curr_L.y - number_pos.y);
            int dist_R = abs(curr_R.x - number_pos.x) + abs(curr_R.y - number_pos.y);
            
            if(dist_L < dist_R){
                curr_L.x = number_pos.x;
                curr_L.y = number_pos.y;
                push_hand = 'L';
            }
            else if(dist_L > dist_R){
                curr_R.x = number_pos.x;
                curr_R.y = number_pos.y;
                push_hand = 'R';
            }
            else{
                if(hand == "left"){
                    curr_L.x = number_pos.x;
                    curr_L.y = number_pos.y;
                    push_hand = 'L';
                }
                else{
                    curr_R.x = number_pos.x;
                    curr_R.y = number_pos.y;
                    push_hand = 'R';
                }
            }
        }
        answer.push_back(push_hand);
    }
    return answer;
}
