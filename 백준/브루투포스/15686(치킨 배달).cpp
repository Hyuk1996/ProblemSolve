#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
const int HOME = 1;
const int CHICKEN = 2;
const int INF = 987654321;


int getCityChickenDist(vector<pair<int, int>>& chicken, vector<int>& combination, vector<pair<int, int>>& homes) {
    int cityChickenDist = 0;
    for(int i=0; i<homes.size(); ++i) {
        int chickenDist = INF;
        for(int j=0; j<combination.size(); ++j) {
            chickenDist = min(chickenDist,
                              abs(homes[i].first - chicken[combination[j]].first) + abs(homes[i].second - chicken[combination[j]].second));
        }
        cityChickenDist += chickenDist;
    }
    return cityChickenDist;
}
void getCombination(vector<pair<int,int>>& chickens, int idx, int curDepth, vector<int>& combination, int limit, vector<pair<int, int>>& homes, int& answer) {
    // 조합이 구해진 경우.
    if(curDepth == limit) {
        answer = min(answer, getCityChickenDist(chickens, combination, homes));
        return;
    }

    for(int i=idx; i<chickens.size(); ++i) {
        combination[curDepth] = i;
        getCombination(chickens, i + 1, curDepth + 1, combination, limit, homes, answer);
    }
}
void getInfo(const vector<vector<int>>& city, const int N, vector<pair<int, int>>& homes, vector<pair<int,int>>& chickens) {
    for(int i=0; i<N; ++i) {
        for(int j=0; j<N; ++j) {
            if(city[i][j] == HOME) {
                homes.push_back(make_pair(i, j));
            } else if(city[i][j] == CHICKEN) {
                chickens.push_back(make_pair(i, j));
            } else {
                continue;
            }
        }
    }
}
int solve(vector<vector<int>>& city, int N, int M) {
    vector<pair<int, int>> homes;
    vector<pair<int, int>> chickens;
    getInfo(city, N, homes, chickens);

    int answer = INF;
    vector<int> combination(M, 0);
    getCombination(chickens, 0, 0, combination, M, homes, answer);

    return answer;
}
void input(vector<vector<int>>& city, int& N, int& M) {
    cin >> N >> M;
    city.assign(N, vector<int>(N, 0));
    for(int i=0; i<N; ++i) {
        for(int j=0; j<N; ++j) {
            cin >> city[i][j];
        }
    }
}
int main() {
    int N, M;
    vector<vector<int>> city;
    input(city, N, M);

    int answer = solve(city, N, M);
    cout << answer;
    return 0;
}
