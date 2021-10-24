#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int main(){
    // 입력.
    int N;
    cin >> N;

    priority_queue<int, vector<int>, less<int> > pq;
    vector<int> ans;
    while(N--){
        int x;
        cin >> x;

        if(x == 0){
            if(pq.empty())
                ans.push_back(0);
            else{
                ans.push_back(pq.top());
                pq.pop();
            }
        }
        else
            pq.push(x);
    }
    // 출력
    for(int i=0; i<ans.size(); i++)
        cout << ans[i] << '\n';

    return 0;
}
