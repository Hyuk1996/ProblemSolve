#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>
using namespace std;

int main(){
    // 입력.
    int T;
    cin >> T;
    vector<int> answers;
    while(T--){
        int N, M;
        cin >> N >> M;
        // queue 생성.
        queue<pair<int, int>> q;
        vector<int> importance;
        for(int i=0; i<N; i++){
            int important;
            cin >> important;
            importance.push_back(important);
            q.push(make_pair(i, important));
        }

        // 시뮬레이션.
        sort(importance.begin(), importance.end(), greater<int>());
        int idx = 0;
        int ans = 1;
        while(!q.empty()) {
            if(q.front().second == importance[idx]){
                if(q.front().first == M){
                    answers.push_back(ans);
                    break;
                }
                else{
                    q.pop();
                    ans++;
                    idx++;
                }
            }
            else{
                q.push(make_pair(q.front().first, q.front().second));
                q.pop();
            }
        }
    }

    // 출력.
    for(int i=0; i<answers.size(); i++)
        cout << answers[i] << '\n';
    return 0;
}
