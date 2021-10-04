#include <string>
#include <vector>
#include <map>

using namespace std;

int solution(vector<vector<string>> clothes) {
    
    // map을 이용해 옷의 종류 기준으로 분류하기.
    map<string, int> m;
    for(int i=0; i<clothes.size(); i++){
        if(m.find(clothes[i][1]) == m.end())
            m[clothes[i][1]] = 1;
        else
            m[clothes[i][1]]++;
    }
    
    // 모든 조합 구하기. (옷의 조합: (옷의 종류 + 1(안입는 경우) * ... * (옷의 종류 + 1)) - 1(모두 안입는 경우))
    map<string, int>::iterator iter;
    int answer = 1;
    for(iter=m.begin(); iter!=m.end(); iter++)
        answer *= (iter->second + 1);
    answer--;
    return answer;
}
