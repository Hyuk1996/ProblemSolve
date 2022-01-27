#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
const int dr[4] = {0, 0, -1, 1};
const int dc[4] = {-1, 1, 0, 0};
struct student {
    int id;
    vector<int> likeStudents;
    int r, c;
    student(int id, int s1, int s2, int s3, int s4) {
        this->id = id;
        likeStudents.push_back(s1);
        likeStudents.push_back(s2);
        likeStudents.push_back(s3);
        likeStudents.push_back(s4);
    };

    void setSeat(int r, int c) {
        this->r = r;
        this->c = c;
    }
};
struct state {
    int likeStudentCnt;
    int emptySeatCnt;
    int r;
    int c;
    state(int likeStudentCnt, int emptySeatCnt, int r, int c) {
        this->likeStudentCnt = likeStudentCnt;
        this->emptySeatCnt = emptySeatCnt;
        this->r = r;
        this->c = c;
    }
};

bool cmp(const state& s1, const state& s2) {
    if(s1.likeStudentCnt == s2.likeStudentCnt) {
        if(s1.emptySeatCnt == s2.emptySeatCnt) {
            if(s1.r == s2.r) {
                return s1.c < s2.c;
            } else {
                return s1.r < s2.r;
            }
        } else {
            return s1.emptySeatCnt > s2.emptySeatCnt;
        }
    }
    return s1.likeStudentCnt > s2.likeStudentCnt;
}
bool isLikeStudent(int id, student& s) {
    for(int i=0; i<4; ++i) {
        if(s.likeStudents[i] == id) {
            return true;
        }
    }
    return false;
}
int getSatisfy(vector<vector<int>>& map, int N, student& s) {
    int likeStudentCnt = 0;
    int r = s.r;
    int c = s.c;
    for(int i=0; i<4; ++i) {
        int nextR = r + dr[i];
        int nextC = c + dc[i];

        if(nextR < 1 || nextR > N || nextC < 1 || nextC > N) {
            continue;
        }

        if(isLikeStudent(map[nextR][nextC], s)) {
            likeStudentCnt++;
        }
    }

    if(likeStudentCnt == 0) {
        return 0;
    } else if(likeStudentCnt == 1) {
        return 1;
    } else if(likeStudentCnt == 2) {
        return 10;
    } else if(likeStudentCnt == 3) {
        return 100;
    } else {
        return 1000;
    }
}
void selectSeat(vector<vector<int>>& map, int N, student& s) {
    vector<state> states;

    int likeStudentCnt, emptySeatCnt;
    for(int r=1; r<=N; ++r) {
        for(int c=1; c<=N; ++c) {
            if(map[r][c] != 0) {
                continue;
            }

            likeStudentCnt = 0;
            emptySeatCnt = 0;

            for(int k=0; k<4; ++k) {
                int nextR = r + dr[k];
                int nextC = c + dc[k];

                if(nextR < 1 || nextR > N || nextC < 1 || nextC > N) {
                    continue;
                }

                if(map[nextR][nextC] == 0) {
                    emptySeatCnt++;
                } else {
                    if(isLikeStudent(map[nextR][nextC], s)) {
                        likeStudentCnt++;
                    }
                }
            }
            states.push_back(state(likeStudentCnt, emptySeatCnt, r, c));
        }
    }

    //후보지를 문제의 요구사항에 맞는 우선순위로 정렬
    sort(states.begin(), states.end(), cmp);
    //가장 첫번째 후보지가 앉을 자리
    map[states[0].r][states[0].c] = s.id;
    s.setSeat(states[0].r, states[0].c);
}
int simulation(int N, vector<student>& students, vector<vector<int>>& map) {
    for(int i=0; i<students.size(); ++i) {
        selectSeat(map, N, students[i]);
    }

    int answer = 0;
    for(int i=0; i<students.size(); ++i) {
        answer += getSatisfy(map, N, students[i]);
    }
    return answer;
}
void input(int& N, vector<student>& students, vector<vector<int>>& map) {
    cin >> N;
    map.assign(N+1, vector<int>(N+1, 0));
    int id, s1, s2, s3, s4;
    for(int i=1; i<=(N*N); ++i) {
        cin >> id >> s1 >> s2 >> s3 >> s4;
        students.push_back(student(id, s1, s2, s3, s4));
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N;
    vector<student> students;
    vector<vector<int>> map;
    input(N, students, map);

    int answer = simulation(N, students, map);

    cout << answer;
    return 0;
}
