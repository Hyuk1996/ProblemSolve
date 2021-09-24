#include <vector>
#include <queue>
#include <iostream>

using namespace std;

// 전역 변수를 정의할 경우 함수 내에 초기화 코드를 꼭 작성해주세요.
vector<int> solution(int m, int n, vector<vector<int>> picture) {
    int number_of_area = 0;
    int max_size_of_one_area = 0;
    
    bool check[100][100] = {0};
    int x_move[4] = {0, 0, -1, 1};
    int y_move[4] = {-1, 1, 0, 0};
    
    for(int i=0; i<m; ++i){
        for(int j=0; j<n; ++j){
            
            
            if(picture[i][j] == 0 || check[i][j])
                continue;
            else{
                queue<pair<int, int>> q;
                int size_of_one_area = 0;
                int color;
                
                q.push(make_pair(j, i));
                size_of_one_area++;
                color = picture[i][j];
                check[i][j] = true;
                
                while(!q.empty()){
                    int tmp_x = q.front().first;
                    int tmp_y = q.front().second;
                    q.pop();
                    
                    int next_x;
                    int next_y;
                    for(int z=0; z<4; ++z){
                        next_x = tmp_x + x_move[z];
                        next_y = tmp_y + y_move[z];
                        if( (0 <= next_x && next_x < n) && (0<= next_y && next_y < m)){
                            if(!check[next_y][next_x] && picture[next_y][next_x] == color){
                                q.push(make_pair(next_x, next_y));
                                check[next_y][next_x] = true;
                                size_of_one_area++;
                            }
                        }
                    }
                }
                max_size_of_one_area = max(max_size_of_one_area, size_of_one_area);
                number_of_area++;
            }
        }
    }
    vector<int> answer(2);
    answer[0] = number_of_area;
    answer[1] = max_size_of_one_area;
    return answer;
}
