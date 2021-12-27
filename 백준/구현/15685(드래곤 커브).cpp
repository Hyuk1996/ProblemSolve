#include <iostream>
#include <vector>
using namespace std;
const int MAX_SIZE = 101;
struct DragonCurve {
    int x;
    int y;
    int d;
    int g;

    DragonCurve(int x, int y, int d, int g) {
        this->x = x;
        this->y = y;
        this->d = d;
        this->g = g;
    }
};


int findSquare(const vector<vector<bool>>& grid) {
    int squareCount = 0;

    for(int i=0; i<MAX_SIZE; ++i) {
        for(int j=0; j<MAX_SIZE; ++j) {
            if(i+1 >= MAX_SIZE || j+1 >= MAX_SIZE) {
                continue;
            }

            if(grid[i][j] && grid[i+1][j] && grid[i][j+1] && grid[i+1][j+1]) {
                ++squareCount;
            }
        }
    }
    return squareCount;
}
void makeDragonCurve(vector<vector<bool>>& grid, DragonCurve& dragonCurve) {
    int dx[4] = {1, 0, -1, 0};
    int dy[4] = {0, -1, 0, 1};

    vector<int> curveDir;
    int x = dragonCurve.x;
    int y = dragonCurve.y;
    int d = dragonCurve.d;
    int g = dragonCurve.g;

    // 0세대 만들기
    grid[y][x] = true;
    curveDir.push_back(d);
    x += dx[d];
    y += dy[d];
    grid[y][x] = true;

    for(int i=0; i<g; ++i) {
        int start = curveDir.size() - 1;
        for(int j=start; j>=0; --j) {
            d = curveDir[j];
            d = (d + 1) % 4;
            curveDir.push_back(d);
            x += dx[d];
            y += dy[d];
            grid[y][x] = true;
        }
    }
}
void makeDragonCurves(vector<vector<bool>>& grid, vector<DragonCurve>& dragonCurves) {
    for(int i=0; i<dragonCurves.size(); ++i) {
        makeDragonCurve(grid, dragonCurves[i]);
    }
}
void input(int& N, vector<DragonCurve>& dragonCurves) {
    cin >> N;
    for(int i=0; i<N; ++i) {
        int x, y, d, g;
        cin >> x >> y >> d >> g;
        dragonCurves.push_back(DragonCurve(x, y, d, g));
    }
}
int main() {
    vector<vector<bool>> grid(MAX_SIZE, vector<bool>(MAX_SIZE, false));

    int N;
    vector<DragonCurve> dragonCurves;
    input(N, dragonCurves);

    makeDragonCurves(grid, dragonCurves);

    int answer = findSquare(grid);
    cout << answer;
    return 0;
}
