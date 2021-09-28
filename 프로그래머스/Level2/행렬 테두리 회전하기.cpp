#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


vector<int> solution(int rows, int columns, vector<vector<int>> queries) {
    vector<int> answer;
    
    vector<vector<int>> matrix(rows + 1, vector<int>(columns + 1, 0));
    int init_value = 1;
    for(int i=1; i<=rows; ++i){
        for(int j=1; j<=columns; ++j){
            matrix[i][j] = init_value;
            init_value++;
        }
    }
    
    for(int i=0; i<queries.size(); ++i){
        int x1 = queries[i][0];
        int y1 = queries[i][1];
        int x2 = queries[i][2];
        int y2 = queries[i][3];
        
        int min_value = 123456789;
        int tmp = matrix[x1][y2];
        // right
        for(int j=y2-1; j>=y1; --j){
            min_value = min(matrix[x1][j], min_value);
            matrix[x1][j+1] = matrix[x1][j];
        }
        
        // down
        int tmp2 = matrix[x2][y2];
        for(int j=x2-1; j>x1; --j){
            min_value = min(matrix[j][y2], min_value);
            matrix[j+1][y2] = matrix[j][y2];
        }
        min_value = min(tmp, min_value);
        matrix[x1+1][y2] = tmp;
        
        // left
        tmp = matrix[x2][y1];
        for(int j=y1+1; j<y2; ++j){
            min_value = min(matrix[x2][j], min_value);
            matrix[x2][j-1] = matrix[x2][j];
        }
        min_value = min(tmp2, min_value);
        matrix[x2][y2-1] = tmp2;
        
        // up
        for(int j=x1+1; j<x2; ++j){
            min_value = min(matrix[j][y1], min_value);
            matrix[j-1][y1] = matrix[j][y1];
        }
        min_value = min(tmp, min_value);
        matrix[x2 - 1][y1] = tmp;
        
        answer.push_back(min_value);
    }
    return answer;
}
