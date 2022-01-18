#include <iostream>
#include <vector>
using namespace std;
const int dr[4] = {0, 0, -1, 1};
const int dc[4] = {-1, 1, 0, 0};

float getAvg(vector<vector<int>>& map, int N, int M) {
    int sum = 0;
    int cnt = 0;
    for(int i=1; i<=N; ++i) {
        for(int j=1; j<=M; ++j) {
            if(map[i][j] != -1) {
                sum += map[i][j];
                cnt++;
            }
        }
    }
    if(cnt == 0) {
        return -1;
    }
    return (sum / (float)cnt);
}
void dfs(vector<vector<int>>& map, int r, int c, int N, int M, int& cnt, int tmp) {
    map[r][c] = -1;
    cnt++;
    for(int i=0; i<4; ++i) {
        int nextR = r + dr[i];
        int nextC = c + dc[i];

        if(nextR < 1 || nextR > N) {
            continue;
        }
        if(nextC == 0) {
            nextC = M;
        }
        if(nextC == M+1) {
            nextC = 1;
        }

        if(map[nextR][nextC] != tmp) {
            continue;
        }
        dfs(map, nextR, nextC, N, M, cnt, tmp);
    }
}
bool eraseAdj(vector<vector<int>>& map, int N, int M) {
    bool isErase = false;
    int tmp, cnt;
    for(int i=1; i<=N; ++i) {
        for(int j=1; j<=M; ++j) {
            if(map[i][j] == -1) {
                continue;
            }
            tmp = map[i][j];
            cnt = 0;
            dfs(map, i, j, N, M, cnt, tmp);
            if(cnt == 1) {
                map[i][j] = tmp;
            } else {
                isErase = true;
            }
        }
    }
    return isErase;
}
void rotation(vector<vector<int>>& map, int x, int d, int k, int N, int M) {
    int circleNum = x;
    while(circleNum <= N) {
        if(d == 0) {
            for(int i=0; i<k; ++i) {
                int tmp = map[circleNum][M];
                for(int j=M; j > 1; --j) {
                    map[circleNum][j] = map[circleNum][j-1];
                }
                map[circleNum][1] = tmp;
            }
        } else {
            for(int i=0; i<k; ++i) {
                int tmp = map[circleNum][1];
                for(int j=1; j < M; ++j) {
                    map[circleNum][j] = map[circleNum][j+1];
                }
                map[circleNum][M] = tmp;
            }
        }
        circleNum += x;
    }
}
int simulation(int N, int M, int T, vector<vector<int>>& map) {
   int x, d, k;
   while(T--) {
       cin >> x >> d >> k;

       rotation(map, x, d, k, N, M);

       if(!eraseAdj(map, N, M)) {
           float avg = getAvg(map, N, M);
           if(avg == -1) { // 모든 숫자가 지워진 경우
               break;
           }

           //평균 더해주기
           for(int i=1; i<=N; ++i) {
               for(int j=1; j<=M; ++j) {
                   if(map[i][j] != -1) {
                       if((float)map[i][j] > avg) {
                           map[i][j]--;
                       } else if((float)map[i][j] < avg){
                           map[i][j]++;
                       }
                   }
               }
           }
       }
   }

   int answer = 0;
   for(int i=1; i<=N; ++i) {
       for(int j=1; j<=M; ++j) {
           if(map[i][j] != -1) {
               answer += map[i][j];
           }
       }
   }
   return answer;
}
void input(int& N, int& M, int& T, vector<vector<int>>& map) {
    cin >> N >> M >> T;
    map.assign(N+1, vector<int>(M+1, 0));
    for(int i=1; i<=N; ++i) {
        for(int j=1; j<=M; ++j) {
            cin >> map[i][j];
        }
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int N, M, T;
    vector<vector<int>> map;
    input(N, M, T, map);

    int answer = simulation(N, M, T, map);

    cout << answer;
    return 0;
}
