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

// 정렬 & 이진탐색 이용한 풀이.
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main(){
    // 입력
    int N;
    cin >> N;
    vector<int> card;
    for(int i=0; i<N; i++){
        int tmp;
        cin >> tmp;
        card.push_back(tmp);
    }
    sort(card.begin(), card.end());

    // 풀이.
    int M;
    cin >> M;
    vector<int> answer;
    for(int i=0; i<M; i++){
        int tmp;
        cin >> tmp;
        if(lower_bound(card.begin(), card.end(), tmp) == card.end())
            answer.push_back(0);
        else{
            answer.push_back(upper_bound(card.begin(), card.end(), tmp) - lower_bound(card.begin(), card.end(), tmp));
        }
    }

    // 출력
    for(int i=0; i<answer.size(); i++)
        cout << answer[i] << ' ';

    return 0;
}
