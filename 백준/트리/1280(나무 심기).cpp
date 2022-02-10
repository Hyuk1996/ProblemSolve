#include <iostream>
#include <vector>
#define MAX 200000
#define MODE 1000000007
using namespace std;

void updateSumIDT(vector<long long>& sumIDT, int p) {
    int idx = p + (sumIDT.size() / 2);
    sumIDT[idx] += p;
    while(idx > 1) {
        idx /= 2;
        sumIDT[idx] = sumIDT[idx * 2] + sumIDT[idx * 2 + 1];
    }
}
long long rangeSum(vector<long long>& sumIDT, int left, int right) {
    left += (sumIDT.size() / 2);
    right += (sumIDT.size() / 2);
    long long sum = 0;
    while(left <= right) {
        if(left % 2 == 1) {
            sum += sumIDT[left];
        }
        if(right % 2 == 0) {
            sum += sumIDT[right];
        }

        left = (left + 1) / 2;
        right = (right - 1) / 2;
    }
    return sum;
}
void updateCntIDT(vector<int>& cntIDT, int p) {
    p += (cntIDT.size() / 2);
    cntIDT[p]++;
    while(p > 1) {
        p /= 2;
        cntIDT[p] = cntIDT[p * 2] + cntIDT[p * 2 + 1];
    }
}
int rangeCnt(vector<int>& cntIDT, int left, int right) {
    left += (cntIDT.size() / 2);
    right += (cntIDT.size() / 2);
    int cnt = 0;
    while(left <= right) {
        if(left % 2 == 1) {
            cnt += cntIDT[left];
        }
        if(right % 2 == 0) {
            cnt += cntIDT[right];
        }

        left = (left + 1) / 2;
        right = (right - 1) / 2;
    }
    return cnt;
}
int getSize() {
   int size = 1;
   while(size < (MAX + 1)) {
       size *= 2;
   }
   return size * 2;
}
int solve(int n, vector<int>& arr) {

    int IDTSize = getSize();

    vector<int> cntIDT(IDTSize, 0);
    vector<long long> sumIDT(IDTSize, 0);

    updateCntIDT(cntIDT, arr[1]);
    updateSumIDT(sumIDT, arr[1]);

    long long leftCnt, rightCnt;
    long long leftSum, rightSum;
    long long answer = 1;
    for(int i = 2; i <= n; ++i) {
        leftCnt = 0;
        leftSum = 0;
        rightCnt = 0;
        rightSum = 0;

        if(arr[i] > 0) {
            leftCnt = rangeCnt(cntIDT, 0, arr[i] - 1);
            leftSum = rangeSum(sumIDT, 0, arr[i] - 1);
        }
        if(arr[i] < MAX) {
            rightCnt = rangeCnt(cntIDT, arr[i] + 1, MAX);
            rightSum = rangeSum(sumIDT, arr[i] + 1, MAX);
        }

        updateCntIDT(cntIDT, arr[i]);
        updateSumIDT(sumIDT, arr[i]);

        int tmp1 = ((leftCnt * arr[i]) - leftSum) % MODE;
        int tmp2 = (rightSum - (rightCnt * arr[i])) % MODE;

        answer = (answer * ((tmp1 + tmp2) % MODE)) % MODE;
    }

    return answer;
}
void input(int& n, vector<int>& arr) {
    cin >> n;
    arr.assign(n + 1, 0);
    for(int i = 1; i <= n; ++i) {
        cin >> arr[i];
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    vector<int> arr;
    input(n, arr);

    int answer = solve(n, arr);

    cout << answer;
    return 0;
}
