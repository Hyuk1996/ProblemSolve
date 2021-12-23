#include <iostream>
#include <vector>
using namespace std;

int main() {
    // 입력.
    int N;
    cin >> N;
    vector<int> examRoom(N, 0);
    for(int i=0; i<N; ++i) {
        int participantCount;
        cin >> participantCount;
        examRoom[i] = participantCount;
    }
    int B, C;
    cin >> B >> C;

    // 각 교실에 필요한 응시자 수 구하기.
    int totalMainSupervisors = 0;
    long long totalSubSupervisors = 0;

    for(int i=0; i<N; ++i) {
        examRoom[i] -= B;
        ++totalMainSupervisors;

        if(examRoom[i] <= 0)
            continue;

        if(examRoom[i] % C == 0) {
            totalSubSupervisors += examRoom[i] / C;
        } else {
            totalSubSupervisors += examRoom[i] / C + 1;
        }
    }

    // 정답 출력.
    long long SupervisorNumbers = totalMainSupervisors + totalSubSupervisors;
    cout << SupervisorNumbers;
}
