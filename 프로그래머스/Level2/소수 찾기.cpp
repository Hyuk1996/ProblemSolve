#include <string>
#include <vector>
#include <map>
#include <cmath>
#include <iostream>

using namespace std;
void getCombi(string& numbers, int size, string combi, vector<bool>& check, map<int, int>& m){
    if(combi.size() == size){
        int tmp = stoi(combi);
        if(m.find(tmp) == m.end())
            m[tmp] = 1;
        return;
    }
    
    for(int i=0; i<numbers.size(); i++){
        if(!check[i]){
            check[i] = true;
            getCombi(numbers, size, combi + numbers[i], check, m);
            check[i] = false;
        }
    }
}
int solution(string numbers) {
    int answer = 0;
    
    map<int, int> m;
    for(int i=1; i<=numbers.size(); i++){
        vector<bool> check(7, 0);
        
        // 길기가 i인 가능한 조합 모두 구하기.
        getCombi(numbers, i, "", check, m);
    }
    
    // 가능한 조합 중 소수 찾기.
    map<int, int>::iterator iter;
    for(iter=m.begin(); iter!=m.end(); iter++){
        bool is_prime = true;
        int num = iter->first;
        // 소수 체크.
        if(num < 2) is_prime = false;
        for(int i=2; i <= sqrt(num); i++){
            if(num % i == 0){
                is_prime = false;
                break;
            }   
        }
        if(is_prime)
            answer++;
    }
    return answer;
}
