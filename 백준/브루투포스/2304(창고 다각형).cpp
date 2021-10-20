#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

bool cmp(const pair<int, int>& a, const pair<int, int>& b){
    return a.first < b.first;
}
int main(){
    // 문제의 변수들 입력받기.
    int N;
    cin >> N;
    vector<pair<int, int>> v; // 기둥 정보 저장.
    for(int i=0; i<N; i++){
        int start_point;
        int h;
        cin >> start_point;
        cin >> h;
        v.push_back(make_pair(start_point, h));
    }

    // 문제 해결.
    // 가둥 정보를 순서대로 정렬.
    sort(v.begin(), v.end(), cmp);
    int cur_y = v[0].second; // 지붕의 현재 높이.
    int ans = cur_y; // 창고 다각형의 면적.
    int cur_x = v[0].first + 1; // 지붕의 현재 위치.
    for(int i=1; i<v.size(); i++){
        if(cur_y <= v[i].second){ // 다음 기둥이 현재 기둥보다 높을 경우.
            ans += (v[i].first - cur_x) * cur_y;

            cur_y = v[i].second;
            ans += cur_y;
            cur_x = v[i].first + 1;
        }
        else { // 다음 기둥이 현재 기둥보다 작음.
            // 남은 기둥 중 가장 높은 기둥인지 확인.
            bool highest = true;
            int tmp = v[i].second;
            for (int j = i + 1; j < v.size(); j++)
                if (tmp < v[j].second) {
                    highest = false;
                    break;
                }

            if (highest) { // 가장 높은 기둥인 경우 지붕이 내려가도 된다.
                cur_y = v[i].second;
                ans += (v[i].first + 1 - cur_x) * cur_y;
                cur_x = v[i].first + 1;
            } else // 다음 기둥에 따라 지붕 높이 결정.
                continue;
        }
    }

    cout << ans;

}

// 새로운 접근 방식.
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
    // 입력 받기.
    int N;
    cin >> N;

    vector<vector<int>> v(1001, vector<int>(3, 0));
    for(int i=0; i<N; i++){
        int x;
        int y;
        cin >> x;
        cin >> y;
        v[x][0] = y;
    }
    // 왼 -> 오른쪽
    int max_value = -1;
    for(int i=1; i<=1000; i++){
        max_value = max(max_value, v[i][0]);
        v[i][1] = max_value;
    }

    // 오른쪽 -> 왼쪽
    max_value = -1;
    for(int i=1000; i>=0; i--){
        max_value = max(max_value, v[i][0]);
        v[i][2] = max_value;
    }

    // 정답 도출
    int ans = 0;
    for(int i=1; i<=1000; i++)
        ans += min(v[i][1], v[i][2]);
    cout << ans;
}
