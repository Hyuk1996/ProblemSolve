#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<int> people, int limit) {
    int answer = 0;
    
    sort(people.begin(), people.end(), less<int>());
    int lightest = 0;
    int heavest = people.size() -1;
    while(lightest <= heavest){
        if(people[lightest] + people[heavest] <= limit){
            lightest++;
            heavest--;
        }
        else{ // 가장 가벼운 사람과 가장 무거운 사람이 같이 못타면, 가장 무거운 사람은 무조건 혼자 타야한다.
            heavest--;
        }
        answer++;
    }
    return answer;
}
