#include <string>
#include <vector>
#include <cmath>
#include <iostream>

using namespace std;

vector<int> solution(int brown, int yellow) {
    vector<int> answer;
    
    int wide = yellow; // 노란색 격자의 가로길이.
    int height = 1; // 노란색 격자의 세로길이.
    int brown_cnt; // 그에 따라 필요한 갈색 격자의 수. 
    // 완전탐색으로 가능한 경우의 수 찾기.
    while(wide >= height){
        //test
        //cout << "wide: " << wide << ", height: " << height << '\n';
        
        brown_cnt = (height * 2) + (wide * 2) + 4;
        if(brown_cnt == brown)
            break;
        
        for(int i=height+1; i <= sqrt(yellow); i++){
            if(yellow % i == 0){
                height = i;
                wide = yellow / height;
                break;
            }
        }
    }
    
    height += 2;
    wide += 2;
    answer.push_back(wide);
    answer.push_back(height);
    return answer;
}
