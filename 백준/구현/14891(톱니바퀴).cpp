#include <iostream>
#include <vector>
#include <string>
using namespace std;

void moveRight(vector<string>& gears, int start_gear, int dir, vector<int>& start_indices, vector<int>& dirs){
    if(start_gear == 3 || dir == 0)
        return;

    if(gears[start_gear][(start_indices[start_gear] + 2) % 8] != gears[start_gear + 1][(start_indices[start_gear + 1] + 6) % 8])
        dir *= -1;
    else
        dir = 0;
    start_gear++;
    dirs[start_gear] = dir;
    moveRight(gears, start_gear, dir, start_indices, dirs);
}
void moveLeft(vector<string>& gears, int start_gear, int dir, vector<int>& start_indices, vector<int>& dirs){
    if(start_gear == 0 || dir == 0)
        return;

    if(gears[start_gear][(start_indices[start_gear] + 6) % 8] != gears[start_gear -1][(start_indices[start_gear - 1] + 2) % 8])
        dir *= -1;
    else
        dir = 0;
    start_gear--;
    dirs[start_gear] = dir;
    moveLeft(gears, start_gear, dir, start_indices, dirs);
}
int main(){
     // 입력, 톱니바퀴 만들기.
     vector<string> gears;
     for(int i=0; i<4; i++){
         string states;
         cin >> states;
         gears.push_back(states);
     }

     // 톱니바퀴 회전
     vector<int> start_indices(4, 0); // 톱니바퀴들의 시작 index(12시)
     int K;
     cin >> K;
     while(K--){
         int start_gear;
         int dir;
         vector<int> dirs(4, 0); // 톱니바퀴들의 회전방향 정보.
         cin >> start_gear >> dir;
         start_gear--;
         dirs[start_gear] = dir;

         // start_gear 기준 오른쪽 톱니바퀴 회전 방향 결정.
         moveRight(gears, start_gear, dir, start_indices, dirs);
         moveLeft(gears, start_gear, dir, start_indices, dirs);

         // 정해진 방향대로 회전하기.
         for(int i=0; i<4; i++){
             if(dirs[i] == 1)
                 start_indices[i] = (start_indices[i] + 7) % 8;
             else if(dirs[i] == -1)
                start_indices[i] = (start_indices[i] + 1) % 8;
         }
     }

     // 정답 구하기.
     int total_score = 0;
     int score = 1;
     for(int i=0; i<4; i++){
         if(gears[i][start_indices[i]] == '1')
             total_score += score;
         score *= 2;
     }
     cout << total_score;
     return 0;
}
