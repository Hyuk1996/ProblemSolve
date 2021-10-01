#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool cmp(const string& a, const string& b){
    return a+b > b+a;
}
string solution(vector<int> numbers) {
    string answer = "";
    
    // int -> string.
    vector<string> v;
    for(int i=0; i<numbers.size(); i++)
        v.push_back(to_string(numbers[i]));
    
    // 정렬.
    sort(v.begin(), v.end(), cmp);
    
    // 0이 여러개일 경우 예외처리.
    if(v[0] == "0") return "0";
    
    for(int i=0; i<v.size(); i++)
        answer += v[i];
    return answer;
}
