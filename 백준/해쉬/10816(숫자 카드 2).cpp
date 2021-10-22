#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

int main(){
    // 입력.
    int N;
    cin >> N;
    unordered_map<int, int> card;
    for(int i=0; i<N; i++){
        int tmp;
        cin >> tmp;
        if(card.find(tmp) != card.end())
            card[tmp]++;
        else
            card[tmp] = 1;
    }

    // 풀이.
    int M;
    cin >> M;
    vector<int> answer;
    for(int i=0; i<M; i++) {
        int tmp;
        cin >> tmp;
        if(card.find(tmp) == card.end())
            answer.push_back(0);
        else
            answer.push_back(card[tmp]);
    }

    // 출력.
    for(int i=0; i<answer.size(); i++)
        cout << answer[i] << ' ';
}
