#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
const int INF = 987654321;

void getAnswer(vector<vector<int>>& A, int N, vector<int>& tmp, int& answer) {
    int x = tmp[0];
    int y = tmp[1];
    int d1 = tmp[2];
    int d2 = tmp[3];

    //인구수 구하기
    vector<int> population(6, 0);
    for(int r=1; r<=N; ++r) {
        for(int c=1; c<=N; ++c) {
            if(r < (x + d1) && c <= y &&!(r >= x && c >= y - (r - x))) {
                population[1] += A[r][c];
            } else if(r <= (x + d2) && c > y && !(r >= x && c <= y + (r - x))) {
               population[2] += A[r][c];
            } else if(r >= (x + d1) && c < (y - d1 + d2) && !(r <= (x + d1 + d2) && c >= (y - d1 + d2) - ((x + d1 + d2) - r))) {
                population[3] += A[r][c];
            } else if(r > (x + d2) && c >= (y - d1 + d2) && !(r <= (x + d1 + d2) && c <= (y -d1 + d2) + ((x + d1 + d2) - r))) {
                population[4] += A[r][c];
            } else {
                population[5] += A[r][c];
            }
        }
    }

    int maxPop = *max_element(population.begin() + 1, population.end());
    int minPop = *min_element(population.begin() + 1, population.end());
    answer = min(answer, maxPop - minPop);
}
void recursive(vector<vector<int>>& A, vector<int>& tmp, int N, int& answer) {
    if(tmp.size() == 4) {
        int x= tmp[0];
        int y = tmp[1];
        int d1 = tmp[2];
        int d2 = tmp[3];

        if((x + d1 + d2) > N) {
            return;
        }
        if((y - d1) < 1 || (y - d1) >= y) {
            return;
        }
        if((y + d2) <= y || (y + d2) > N) {
            return;
        }
        getAnswer(A, N, tmp, answer);
        return;
    }
    for(int i=1; i<=N; ++i) {
        tmp.push_back(i);
        recursive(A, tmp, N, answer);
        tmp.pop_back();
    }
}
int solve(int N, vector<vector<int>>& A) {
    //모든 경계 조합 구하기
    vector<int> tmp;
    int answer = INF;
    recursive(A, tmp, N, answer);

    return answer;
}
void input(int& N, vector<vector<int>>& A) {
    cin >> N;
    A.assign(N+1, vector<int>(N+1, 0));
    for(int i=1; i<=N; ++i) {
        for(int j=1; j<=N; ++j) {
            cin >> A[i][j];
        }
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N;
    vector<vector<int>> A;
    input(N, A);

    int answer = solve(N, A);

    cout << answer;
    return 0;
}
