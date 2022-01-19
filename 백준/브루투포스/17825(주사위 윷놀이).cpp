#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
const int START = 0;
const int END = 32;
struct vertex {
    int num;
    int next;
    int specialNext;
    vertex(int num, int next, int specialNext) {
        this->num = num;
        this->next = next;
        this->specialNext = specialNext;
    }
};


int getScore(vector<int>& score) {
    int scoreSum = 0;
    for(int i=0; i<score.size(); ++i) {
        scoreSum += score[i];
    }
    return scoreSum;
}
int getDest(vector<vertex>& map, int moveCnt, int curIdx) {
    if(curIdx == 5 || curIdx == 10 || curIdx == 15) {
        curIdx = map[curIdx].specialNext;
        moveCnt--;
    }
    while(curIdx < END && moveCnt > 0) {
        curIdx = map[curIdx].next;
        moveCnt--;
    }
    return curIdx;
}
bool check(vector<int>& horse, int h, int dest) {
    for(int i=0; i<horse.size(); ++i) {
        if(h == i) {
            continue;
        }
        if(horse[i] == dest) {
            return false;
        }
    }
    return true;
}
void recursive(vector<vertex>& map, vector<int>& move, vector<int>& horse, vector<int>& score, int depth, int& answer) {
    if(depth == 10) {
        answer = max(getScore(score), answer);
        return;
    }
    int dest;
    int tmp;
    for(int i=0; i<4; ++i) {
        dest = getDest(map, move[depth], horse[i]);
        if(check(horse, i, dest) || dest == END) {
            tmp = horse[i];
            horse[i] = dest;
            score[i] += map[dest].num;
            recursive(map, move, horse, score, depth + 1, answer);
            horse[i] = tmp;
            score[i] -= map[dest].num;
        }
    }
}
int solve(vector<int>& move, vector<vertex>& map) {
    vector<int> horses(4, START); // 말의 현재 위치 정보
    vector<int> score(4, 0); // 말들의 현재 점수
    int answer = -1;

    //모든 경우의 수 (중복 순열)
    recursive(map, move, horses, score, 0, answer);
    return answer;
}
void input(vector<int>& move, vector<vertex>& map) {
    move.assign(10, 0);
    for(int i=0; i<10; ++i) {
        cin >> move[i];
    }
    //문제의 게임판을 그래프로 표현
    //시작 정점
    map.push_back(vertex(0, 1, -1));
    for(int i=1; i<=20; ++i) {
        map.push_back(vertex((i * 2), (i+1), -1));
    }
    map[20].next = END;

    map[5].specialNext = 21;
    map.push_back(vertex(13, 22, -1)); //21
    map.push_back(vertex(16, 23, -1));  //22
    map.push_back(vertex(19, 24, -1));  //23
    map.push_back(vertex(25, 30, -1));  //24

    map[10].specialNext = 25;
    map.push_back(vertex(22, 26, -1)); //25
    map.push_back(vertex(24, 24, -1)); //26

    map[15].specialNext = 27;
    map.push_back(vertex(28, 28, -1)); //27
    map.push_back(vertex(27, 29, -1)); //28
    map.push_back(vertex(26, 24, -1)); //29

    map.push_back(vertex(30, 31, -1)); //30
    map.push_back(vertex(35, 20, -1)); //31

    map.push_back(vertex(0, 0, -1)); //32
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    vector<int> move;
    vector<vertex> map;
    input(move, map);

    int answer = solve(move, map);

    cout << answer;
    return 0;
}
