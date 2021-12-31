#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
const int dr[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
const int dc[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
struct tree {
    int r;
    int c;
    int age;

    tree(int r, int c, int age) {
        this->r = r;
        this->c = c;
        this->age = age;
    }
};


bool cmp(const tree& a, const tree& b) {
    return a.age < b.age;
}
void winter(vector<vector<int>>& ground, vector<vector<int>>& s2d2) {
    for(int i=0; i<s2d2.size(); ++i) {
        for(int j=0; j<s2d2.size(); ++j) {
            ground[i][j] += s2d2[i][j];
        }
    }
}
void fall(vector<vector<int>>& ground, deque<tree>& trees, vector<tree>& growTrees) {

    for(int i=0; i<growTrees.size(); ++i) {
        int r = growTrees[i].r;
        int c = growTrees[i].c;
        int age = growTrees[i].age;

        trees.push_back(tree(r, c, age));

        if(age % 5 != 0) {
            continue;
        }

        for(int j=0; j<8; ++j) {
            int nextR = r + dr[j];
            int nextC = c + dc[j];

            if(nextR < 0 || nextR >= ground.size() || nextC < 0 || nextC >= ground.size()) {
                continue;
            }
            trees.push_front(tree(nextR, nextC, 1));
        }
    }
}
void summer(vector<vector<int>>& ground, vector<tree>& deadTrees) {
    for(int i=0; i<deadTrees.size(); ++i) {
        ground[deadTrees[i].r][deadTrees[i].c] += deadTrees[i].age / 2;
    }
}
void spring(vector<vector<int>>& ground, deque<tree>& trees, vector<tree>& deadTrees, vector<tree>& growTrees) {

    while(!trees.empty()) {
        int r = trees.front().r;
        int c = trees.front().c;
        int age = trees.front().age;
        trees.pop_front();

        if(ground[r][c] < age) {
            deadTrees.push_back(tree(r, c, age));
        } else {
            ground[r][c] -= age;
            growTrees.push_back(tree(r, c, age + 1));
        }
    }
}
int solve(vector<vector<int>>& ground, vector<vector<int>>& s2d2, deque<tree>& trees, int K) {
    int curYear = 0;
    sort(trees.begin(), trees.end(), cmp);
    do{
        vector<tree> deadTrees;
        vector<tree> growTrees;

        spring(ground, trees, deadTrees, growTrees);

        summer(ground, deadTrees);

        fall(ground, trees, growTrees);

        winter(ground, s2d2);

        ++curYear;
    } while(curYear < K);
    return (int)trees.size();
}
void input(int& N, int& M, int& K, vector<vector<int>>& ground, vector<vector<int>>& s2d2, deque<tree>& trees) {
    cin >> N >> M >> K;
    ground.assign(N, vector<int>(N, 5));
    s2d2.assign(N, vector<int>(N, 0));
    for(int i=0; i<N; ++i) {
        for(int j=0; j<N; ++j) {
            cin >> s2d2[i][j];
        }
    }

    for(int i=0; i<M; ++i) {
        int x, y, z;
        cin >> x >> y >> z;
        trees.push_back(tree(x-1, y-1, z));
    }
}
int main() {

    int N, M, K;
    vector<vector<int>> ground;
    vector<vector<int>> s2d2;
    deque<tree> trees;
    input(N, M, K, ground, s2d2, trees);

    int answer = solve(ground, s2d2, trees, K);
    cout << answer;
    return 0;
}
