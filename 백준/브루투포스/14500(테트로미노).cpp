#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;
const int dy[4] = {0, 0, -1, 1};
const int dx[4] = {-1, 1, 0, 0};

void test(const vector<vector<int>>& paper) {
    for(int i=0; i<paper.size(); ++i) {
        for(int j=0; j<paper[i].size(); ++j) {
            cout << paper[i][j] << ' ';
        }
        cout << '\n';
    }
}
void bfs(const vector<vector<int>>& paper, int y, int x, int& maxSum) {
    queue<pair<int, int>> q;

    for(int i=0; i<4; ++i) {
        int nextY = y + dy[i];
        int nextX = x + dx[i];

        if(nextY < 0 || nextY >= paper.size() || nextX < 0 || nextX >= paper[y].size()) {
            continue;
        }

        q.push(make_pair(nextY, nextX));
    }

    if(q.size() < 3)
        return;

    int sum = paper[y][x];
    if(q.size() == 3) {
        while(!q.empty()) {
            int tmpY = q.front().first;
            int tmpX = q.front().second;
            q.pop();

            sum += paper[tmpY][tmpX];
        }
        maxSum = max(maxSum, sum);
    } else {
        vector<int> values;
        while(!q.empty()) {
            int tmpY = q.front().first;
            int tmpX = q.front().second;
            q.pop();

            values.push_back(paper[tmpY][tmpX]);
            sum += paper[tmpY][tmpX];
        }

        for(int i=0; i<4; ++i) {
            sum -= values[i];
            maxSum = max(maxSum, sum);
            sum += values[i];
        }
    }
}
void dfs(vector<vector<int>>& paper, int y, int x, int sum, int depth, int& maxSum) {
    if(depth == 4) {
        maxSum = max(maxSum, sum);
        return;
    }

    int tmp = paper[y][x];
    paper[y][x] = -1;
    for(int i=0; i<4; ++i) {
        int nextY = y + dy[i];
        int nextX = x + dx[i];

        if(nextY < 0 || nextY >= paper.size() || nextX < 0 || nextX >= paper[y].size()) {
            continue;
        }
        if(paper[nextY][nextX] == -1) {
            continue;
        }
        dfs(paper, nextY, nextX, sum + paper[nextY][nextX], depth + 1, maxSum);
    }
    paper[y][x] = tmp;
}
int main() {
    // 입력;
    int N, M;
    cin >> N >> M;
    vector<vector<int>> paper(N, vector<int>(M));
    for(int i=0; i<N; ++i) {
        for(int j=0; j<M; ++j) {
            int num;
            cin >> num;
            paper[i][j] = num;
        }
    }

    // dfs 이용해 ㅡ, ㅁ, ㄴ, ㄹ 모양의 테트로미노를 종이의 모든 곳에 두는 경우를 생각해 최대 합 구하기.
    int maxSum = -1;
    for(int i=0; i<N; ++i) {
        for(int j=0; j<M; ++j) {
            dfs(paper, i, j, paper[i][j], 1, maxSum);
        }
    }

    // bfs 이용해 ㅜ 모양의 테트로미노를 종이의 모든 곳에 두는 경우의 수 생각해 최대 합 구하기.
    for(int i=0; i<N; ++i) {
        for(int j=0; j<M; ++j) {
            bfs(paper, i, j, maxSum);
        }
    }

    // 정답 출력.
    cout << maxSum;
    return 0;
}
