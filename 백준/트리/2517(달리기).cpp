#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void updateIDT(vector<int>& IDT, int idx) {
    idx += (IDT.size() / 2);
    IDT[idx]++;
    while(idx > 1) {
        idx /= 2;
        IDT[idx] = IDT[idx * 2] + IDT[idx * 2 + 1];
    }
}
int rangeSum(vector<int>& IDT, int left) {
    left += (IDT.size() / 2);
    int right = IDT.size() - 1;
    int sum = 0;
    while(left <= right) {
        if(left % 2 == 1) {
            sum += IDT[left];
        }
        if(right % 2 == 0) {
            sum += IDT[right];
        }

        left = (left + 1) / 2;
        right = (right - 1) / 2;
    }
    return sum;
}
int binarySearch(vector<int>& order, int key) {
    int lo = 0;
    int hi = order.size();
    int mid;
    while(lo + 1 < hi) {
        mid = lo + (hi - lo) / 2;
        if(order[mid] <= key) {
            lo = mid;
        } else {
            hi = mid;
        }
    }
    return lo;
}
int getIDTSize(int N) {
    int leafSize = 1;
    while(leafSize < N) {
        leafSize *= 2;
    }

    return leafSize * 2;
}
void solve(int& N, vector<int>& players, vector<int>& idealScore) {
    int IDTSize = getIDTSize(N);
    vector<int> IDT(IDTSize, 0);

    vector<int> order(players);
    sort(order.begin(), order.end());

    for(int i = 0; i < N; ++i) {
        int idx = binarySearch(order, players[i]);
        
        int sum = rangeSum(IDT, idx);
        idealScore[i] = sum + 1;

        updateIDT(IDT, idx);
    }
}
void input(int& N, vector<int>& players) {
    cin >> N;
    players.assign(N, 0);
    for(int i = 0; i < N; ++i) {
        cin >> players[i];
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N;
    vector<int> players;
    input(N, players);

    vector<int> idealScore(N, 0);
    solve(N, players, idealScore);

    for(int i = 0; i < N; ++i) {
        cout << idealScore[i] << '\n';
    }
    return 0;
}
