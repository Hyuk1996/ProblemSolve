#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
const int ROOT = 0;

void dfs(const vector<vector<pair<int, int>>>& tree, int v, vector<long long>& distSum, const vector<int>& subtreeCount) {

    for(int i=0; i<tree[v].size(); ++i) {
        int nextV = tree[v][i].first;
        int weight = tree[v][i].second;

        if(distSum[nextV] != 0)
            continue;

        distSum[nextV] = distSum[v] - (subtreeCount[nextV] * weight) + ((tree.size() - subtreeCount[nextV]) * weight);
        dfs(tree, nextV, distSum, subtreeCount);
    }
}
void dfs(const vector<vector<pair<int, int>>>& tree, int v, vector<int>& dist, vector<int>& subtreeCount) {
    subtreeCount[v] = 1;

    for(int i=0; i<tree[v].size(); ++i) {
        int nextV = tree[v][i].first;
        int weight = tree[v][i].second;

        if(dist[nextV] != -1)
            continue;

        dist[nextV] = dist[v] + weight;
        dfs(tree, nextV, dist, subtreeCount);
        subtreeCount[v] += subtreeCount[nextV];
    }
}
int main() {
    vector<long long> answers;

    // 입력.
    while(true) {
        int n;
        cin >> n;

        if(n == 0)
            break;

        // 트리 만들기.
        vector<vector<pair<int, int>>> tree(n);
        for(int i=0; i<n-1; ++i) {
            int a, b, w;
            cin >> a >> b >> w;

            tree[a].push_back(make_pair(b, w));
            tree[b].push_back(make_pair(a, w));
        }

        // dfs 이용, 하나의 root에서 모든 정점들까지 거리의 합, 각 정점들의 subtree에 포함된 정점 개수 구하기.
        vector<int> dist(n, -1);
        vector<int> subtreeCount(n, 0);
        dist[ROOT] = 0;

        dfs(tree, ROOT, dist, subtreeCount);

        // 위에서 구한 정보 이용해 중앙 한 정점에서 다른 정점들까지의 거리 총합 구하기.
        vector<long long> distSum(n, 0);
        for(int i=0; i<n; ++i)
            distSum[ROOT] += dist[i];
        dfs(tree, ROOT, distSum, subtreeCount);

        // 정답 구하기.
        long long answer = *min_element(distSum.begin(), distSum.end());
        answers.push_back(answer);
    }

    // 정답 출력.
    for(long long answer : answers)
        cout << answer << '\n';
    return 0;
}
