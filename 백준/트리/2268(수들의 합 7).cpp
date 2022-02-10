#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void updateIDT(vector<long long>& IDT, int idx, int value) {
    idx += (IDT.size() / 2) - 1;
    IDT[idx] = value;
    while(idx > 1) {
        idx /= 2;
        IDT[idx] = IDT[idx * 2] + IDT[idx * 2 + 1];
    }
}
long long rangeSum(vector<long long>& IDT, int left, int right) {
    left += (IDT.size() / 2) - 1;
    right += (IDT.size() / 2) - 1;
    long long sum = 0;
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
void makeIDT(vector<long long>& IDT, int N) {
    int leafSize = 1;
    while(leafSize < N) {
        leafSize *= 2;
    }

    IDT.assign(leafSize * 2, 0);
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N, M;
    cin >> N >> M;

    vector<long long> IDT;
    makeIDT(IDT, N);

    int a, b, c;
    while(M--) {
        cin >> a >> b >> c;
        if(a == 0) {
            if(b > c) {
                swap(b, c);
            }
            cout << rangeSum(IDT, b, c) << '\n';
        } else {
            updateIDT(IDT, b, c);
        }
    }

    return 0;
}
