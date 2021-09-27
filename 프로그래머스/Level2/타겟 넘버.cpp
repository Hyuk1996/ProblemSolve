#include <string>
#include <vector>
using namespace std;

void DFS(vector<int> &numbers, int target, int depth, int result, int &answer){
    if(depth == numbers.size()){
        if(result == target)
            answer++;
        return;
    }
    
    for(int i=0; i<2; ++i){
        int tmp;
        if(i == 0)
            tmp = numbers[depth];
        else
            tmp = numbers[depth] * (-1);
        DFS(numbers, target, depth + 1, result + tmp, answer);    
    }
}

int solution(vector<int> numbers, int target) {
    int answer = 0;
    
    DFS(numbers, target, 0, 0, answer);
    return answer;
}
