#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> solution(vector<int> array, vector<vector<int>> commands) {
    vector<int> answer;
    
    int i,j,k;
    vector<int> sub_array;
    int ans;
    for(int idx=0; idx<commands.size(); ++idx){
        i = commands[idx][0];
        j = commands[idx][1];
        k = commands[idx][2];
        
        for(int x=i-1; x<j; ++x)
            sub_array.push_back(array[x]);
        sort(sub_array.begin(), sub_array.end());
        ans = sub_array[k-1];
        answer.push_back(ans);
        
        sub_array.clear();
    }
    return answer;
}
