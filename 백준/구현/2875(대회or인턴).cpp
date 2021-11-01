#include <iostream>
using namespace std;

int main(){
    // 입력.
    int N, M, K;
    cin >> N >> M >> K;

    // 만들수 있는 팀 숫자 구하기.
    int team_cnt = 0;
    if( (N / 2) >= M){
        team_cnt = M;
        N -= team_cnt * 2;
        M -= team_cnt;
    }
    else{
        team_cnt = N / 2;
        N -= team_cnt * 2;
        M -= team_cnt;
    }

    // K명 제외.
    int no_team = N + M;
    if(no_team < K){
        K -= no_team;
        if(K % 3 == 0)
            K = K / 3;
        else
            K = K / 3 + 1;
        team_cnt -= K;
    }

    // 정답 출력.
    if(team_cnt < 0)
        team_cnt = 0;
    cout << team_cnt;
    return 0;
}
