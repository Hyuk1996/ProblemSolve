// 첫 번째 풀이. 시간복잡도 O(n^2) (권장 풀이 x)
#include <string>
#include <vector>

using namespace std;

vector<int> solution(vector<int> prices) {
    vector<int> answer(prices.size(), 1);
    
    for(int i=0; i<prices.size(); i++){
        for(int j=i+1; j<prices.size(); j++){
            if(prices[j] >= prices[i])
                answer[i]++;
            else
                break;
        }
    }
    
    for(int i=0; i<answer.size(); i++)
        if(answer[i] == answer.size() - i)
            answer[i]--;
    return answer;
}

// 두 번째 풀이. 시간복잡도 O(n)
#include <string>
#include <vector>
#include <stack>

using namespace std;

vector<int> solution(vector<int> prices) {
    vector<int> answer(prices.size(), 0);
    
    stack<int> s;
    int len = prices.size();
    for(int i=0; i<len; i++){
        while(!s.empty() && prices[s.top()] > prices[i]){
            answer[s.top()] = i - s.top();
            s.pop();
        }
        s.push(i);
    }
    
    while(!s.empty()){
        answer[s.top()] = len - s.top() - 1;
        s.pop();
    }
    return answer;
}
