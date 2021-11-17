#include <iostream>
#include <vector>
#include <map>
using namespace std;

int main(){
    // 입력 속도 높여주기.
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // 입력. map 자료구조 이용해 정렬과 중복제거 동시에 진행.
    int N;
    cin >> N;
    map<int, vector<int>> m;
    for(int i=0; i<N; i++){
        int val;
        cin >> val;
        m[val].push_back(i);
    }

    // 압축 결과 answers vector에 넣어주기.
    int cnt = 0;
    vector<int> answers(N);
    for(auto it = m.begin(); it != m.end(); it++){
        vector<int> tmp = it->second;
        for(int i=0; i<tmp.size(); i++)
            answers[tmp[i]] = cnt;
        ++cnt;
    }

    // 출력.
    for(int i=0; i<answers.size(); i++)
        cout << answers[i] << ' ';
    return 0;
}
