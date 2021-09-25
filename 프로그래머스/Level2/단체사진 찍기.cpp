#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// 전역 변수를 정의할 경우 함수 내에 초기화 코드를 꼭 작성해주세요.
int solution(int n, vector<string> data) {
    int answer = 0;
    
    string kakao_friends = "ACFJMNRT";
    
    do{
        bool flag = true;
        for(int i=0; i<data.size(); ++i){
            char friend1 = data[i][0];
            char friend2 = data[i][2];
            char op = data[i][3];
            int num = data[i][4] - '0';
            int diff = kakao_friends.find(friend1) - kakao_friends.find(friend2);
            diff = abs(diff) - 1;
            
            if( op == '='){
                if(num != diff)
                    flag = false;
            }
            else if(op == '>'){
                if(num >= diff)
                    flag = false;
            }
            else if(op == '<'){
                if(num <= diff)
                    flag = false;
            }
            
            if(!flag)
                break;
        }
        if(flag)
            answer++;
    }while(next_permutation(kakao_friends.begin(), kakao_friends.end()));
    return answer;
}
