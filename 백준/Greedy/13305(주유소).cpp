#include <iostream>
#include <vector>
using namespace std;

int main(){
    // 입력.
    int N;
    cin >> N;
    vector<int> distances(N-1, 0);
    for(int i=0; i<N-1; i++){
        int distance;
        cin >> distance;
        distances[i] = distance;
    }
    vector<int> costs(N, 0);
    for(int i=0; i<N; i++){
        int cost;
        cin >> cost;
        costs[i] = cost;
    }

    // Greedy method 이용해 최적해 구하기.
    long long total_cost = 0;
    for(int i=0; i<N-1;){
        int sub_dist = distances[i];
        int cost = costs[i];
        for(int j=i+1; j<N; j++){
            if(cost >= costs[j] || j == N-1){
                i = j;
                break;
            }
            else
                sub_dist += distances[j];
        }
        total_cost += (long long)sub_dist * (long long)cost;
    }

    // 정답 출력.
    cout << total_cost;
    return 0;
}
