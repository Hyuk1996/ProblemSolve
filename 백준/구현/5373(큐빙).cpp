#include <iostream>
#include <vector>
#include <string>
#include <queue>
using namespace std;
const int CUBE_SIZE = 6;
const int U = 0;
const int D = 1;
const int F = 2;
const int B = 3;
const int L = 4;
const int R = 5;


void printResult(vector<string>& result) {
    for(int i=0; i<result.size(); ++i) {
        cout << result[i] << '\n';
    }
}
void rotateFace(vector<vector<char>>& cube, int face, char dir) {
    if(dir == '+') {
        char tmp1 = cube[face][0];
        cube[face][0] = cube[face][6];
        cube[face][6] = cube[face][8];
        cube[face][8] = cube[face][2];
        cube[face][2] = tmp1;

        char tmp2 = cube[face][1];
        cube[face][1] = cube[face][3];
        cube[face][3] = cube[face][7];
        cube[face][7] = cube[face][5];
        cube[face][5] = tmp2;
    } else {
        char tmp1 = cube[face][0];
        cube[face][0] = cube[face][2];
        cube[face][2] = cube[face][8];
        cube[face][8] = cube[face][6];
        cube[face][6] = tmp1;

        char tmp2 = cube[face][1];
        cube[face][1] = cube[face][5];
        cube[face][5] = cube[face][7];
        cube[face][7] = cube[face][3];
        cube[face][3] = tmp2;
    }
}
void rotation(vector<vector<char>>& cube, int face, char dir) {
    if(face == 'U') {
        rotateFace(cube, U, dir);
        if(dir == '+') {
            char tmp1, tmp2, tmp3;
            tmp1 = cube[R][0];
            tmp2 = cube[R][1];
            tmp3 = cube[R][2];

            cube[R][0] = cube[B][0];
            cube[R][1] = cube[B][1];
            cube[R][2] = cube[B][2];

            cube[B][0] = cube[L][0];
            cube[B][1] = cube[L][1];
            cube[B][2] = cube[L][2];

            cube[L][0] = cube[F][0];
            cube[L][1] = cube[F][1];
            cube[L][2] = cube[F][2];

            cube[F][0] = tmp1;
            cube[F][1] = tmp2;
            cube[F][2] = tmp3;
        } else {
            char tmp1, tmp2, tmp3;
            tmp1 = cube[R][0];
            tmp2 = cube[R][1];
            tmp3 = cube[R][2];

            cube[R][0] = cube[F][0];
            cube[R][1] = cube[F][1];
            cube[R][2] = cube[F][2];

            cube[F][0] = cube[L][0];
            cube[F][1] = cube[L][1];
            cube[F][2] = cube[L][2];

            cube[L][0] = cube[B][0];
            cube[L][1] = cube[B][1];
            cube[L][2] = cube[B][2];

            cube[B][0] = tmp1;
            cube[B][1] = tmp2;
            cube[B][2] = tmp3;
        }
    } else if(face == 'D') {
        rotateFace(cube, D, dir);

        if(dir == '+') {
            char tmp1, tmp2, tmp3;
            tmp1 = cube[F][6];
            tmp2 = cube[F][7];
            tmp3 = cube[F][8];

            cube[F][6] = cube[L][6];
            cube[F][7] = cube[L][7];
            cube[F][8] = cube[L][8];

            cube[L][6] = cube[B][6];
            cube[L][7] = cube[B][7];
            cube[L][8] = cube[B][8];

            cube[B][6] = cube[R][6];
            cube[B][7] = cube[R][7];
            cube[B][8] = cube[R][8];

            cube[R][6] = tmp1;
            cube[R][7] = tmp2;
            cube[R][8] = tmp3;
        } else {
            char tmp1, tmp2, tmp3;
            tmp1 = cube[F][6];
            tmp2 = cube[F][7];
            tmp3 = cube[F][8];

            cube[F][6] = cube[R][6];
            cube[F][7] = cube[R][7];
            cube[F][8] = cube[R][8];

            cube[R][6] = cube[B][6];
            cube[R][7] = cube[B][7];
            cube[R][8] = cube[B][8];

            cube[B][6] = cube[L][6];
            cube[B][7] = cube[L][7];
            cube[B][8] = cube[L][8];

            cube[L][6] = tmp1;
            cube[L][7] = tmp2;
            cube[L][8] = tmp3;
        }
    } else if(face == 'F') {
        rotateFace(cube, F, dir);

        if(dir == '+') {
            char tmp1, tmp2, tmp3;
            tmp1 = cube[U][6];
            tmp2 = cube[U][7];
            tmp3 = cube[U][8];

            cube[U][6] = cube[L][8];
            cube[U][7] = cube[L][5];
            cube[U][8] = cube[L][2];

            cube[L][8] = cube[D][2];
            cube[L][5] = cube[D][1];
            cube[L][2] = cube[D][0];

            cube[D][2] = cube[R][0];
            cube[D][1] = cube[R][3];
            cube[D][0] = cube[R][6];

            cube[R][0] = tmp1;
            cube[R][3] = tmp2;
            cube[R][6] = tmp3;
        } else {
            char tmp1, tmp2, tmp3;
            tmp1 = cube[U][6];
            tmp2 = cube[U][7];
            tmp3 = cube[U][8];

            cube[U][6] = cube[R][0];
            cube[U][7] = cube[R][3];
            cube[U][8] = cube[R][6];

            cube[R][0] = cube[D][2];
            cube[R][3] = cube[D][1];
            cube[R][6] = cube[D][0];

            cube[D][2] = cube[L][8];
            cube[D][1] = cube[L][5];
            cube[D][0] = cube[L][2];

            cube[L][8] = tmp1;
            cube[L][5] = tmp2;
            cube[L][2] = tmp3;
        }
    } else if(face == 'B') {
        rotateFace(cube, B, dir);

        if(dir == '+') {
            char tmp1, tmp2, tmp3;
            tmp1 = cube[U][0];
            tmp2 = cube[U][1];
            tmp3 = cube[U][2];

            cube[U][0] = cube[R][2];
            cube[U][1] = cube[R][5];
            cube[U][2] = cube[R][8];

            cube[R][2] = cube[D][8];
            cube[R][5] = cube[D][7];
            cube[R][8] = cube[D][6];

            cube[D][8] = cube[L][6];
            cube[D][7] = cube[L][3];
            cube[D][6] = cube[L][0];

            cube[L][6] = tmp1;
            cube[L][3] = tmp2;
            cube[L][0] = tmp3;
        } else {
            char tmp1, tmp2, tmp3;
            tmp1 = cube[U][0];
            tmp2 = cube[U][1];
            tmp3 = cube[U][2];

            cube[U][0] = cube[L][6];
            cube[U][1] = cube[L][3];
            cube[U][2] = cube[L][0];

            cube[L][6] = cube[D][8];
            cube[L][3] = cube[D][7];
            cube[L][0] = cube[D][6];

            cube[D][8] = cube[R][2];
            cube[D][7] = cube[R][5];
            cube[D][6] = cube[R][8];

            cube[R][2] = tmp1;
            cube[R][5] = tmp2;
            cube[R][8] = tmp3;
        }
    } else if(face == 'L') {
        rotateFace(cube, L, dir);

        if(dir == '+') {
            char tmp1, tmp2, tmp3;
            tmp1 = cube[F][0];
            tmp2 = cube[F][3];
            tmp3 = cube[F][6];

            cube[F][0] = cube[U][0];
            cube[F][3] = cube[U][3];
            cube[F][6] = cube[U][6];

            cube[U][0] = cube[B][8];
            cube[U][3] = cube[B][5];
            cube[U][6] = cube[B][2];

            cube[B][8] = cube[D][0];
            cube[B][5] = cube[D][3];
            cube[B][2] = cube[D][6];

            cube[D][0] = tmp1;
            cube[D][3] = tmp2;
            cube[D][6] = tmp3;
        } else {
            char tmp1, tmp2, tmp3;
            tmp1 = cube[F][0];
            tmp2 = cube[F][3];
            tmp3 = cube[F][6];

            cube[F][0] = cube[D][0];
            cube[F][3] = cube[D][3];
            cube[F][6] = cube[D][6];

            cube[D][0] = cube[B][8];
            cube[D][3] = cube[B][5];
            cube[D][6] = cube[B][2];

            cube[B][8] = cube[U][0];
            cube[B][5] = cube[U][3];
            cube[B][2] = cube[U][6];

            cube[U][0] = tmp1;
            cube[U][3] = tmp2;
            cube[U][6] = tmp3;
        }
    } else if(face == 'R') {
        rotateFace(cube, R, dir);

        if(dir == '+') {
            char tmp1, tmp2, tmp3;
            tmp1 = cube[F][2];
            tmp2 = cube[F][5];
            tmp3 = cube[F][8];

            cube[F][2] = cube[D][2];
            cube[F][5] = cube[D][5];
            cube[F][8] = cube[D][8];

            cube[D][2] = cube[B][6];
            cube[D][5] = cube[B][3];
            cube[D][8] = cube[B][0];

            cube[B][6] = cube[U][2];
            cube[B][3] = cube[U][5];
            cube[B][0] = cube[U][8];

            cube[U][2] = tmp1;
            cube[U][5] = tmp2;
            cube[U][8] = tmp3;
        } else {
            char tmp1, tmp2, tmp3;
            tmp1 = cube[F][2];
            tmp2 = cube[F][5];
            tmp3 = cube[F][8];

            cube[F][2] = cube[U][2];
            cube[F][5] = cube[U][5];
            cube[F][8] = cube[U][8];

            cube[U][2] = cube[B][6];
            cube[U][5] = cube[B][3];
            cube[U][8] = cube[B][0];

            cube[B][6] = cube[D][2];
            cube[B][3] = cube[D][5];
            cube[B][0] = cube[D][8];

            cube[D][2] = tmp1;
            cube[D][5] = tmp2;
            cube[D][8] = tmp3;
        }
    }
}
void simulation(const vector<string>& rotationInfos, vector<string>& result) {
    vector<vector<char>> cube(CUBE_SIZE);
    for(int i=0; i<9; ++i) {
        cube[U].push_back('w');
        cube[D].push_back('y');
        cube[F].push_back('r');
        cube[B].push_back('o');
        cube[L].push_back('g');
        cube[R].push_back('b');
    }

    for(int i=0; i<rotationInfos.size(); ++i) {
        rotation(cube, rotationInfos[i][0], rotationInfos[i][1]);
    }

    string str = "";
    for(int i=0; i<9; ++i) {
        str += cube[U][i];

        if(str.size() == 3) {
            result.push_back(str);
            str.clear();
        }
    }
}
void input(vector<string>& rotationInfos, int& n) {
    cin >> n;
    for(int i=0; i<n; ++i) {
        string rotationInfo;
        cin >> rotationInfo;
        rotationInfos.push_back(rotationInfo);
    }
}
int main() {
    vector<string> result;

    int testCase;
    cin >> testCase;
    while(testCase--) {
        int n;
        vector<string> rotationInfos;
        input(rotationInfos, n);


        simulation(rotationInfos, result);
    }

    printResult(result);
    return 0;
}
