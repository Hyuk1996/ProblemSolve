# 백준 6603

[문제 출처](https://www.acmicpc.net/problem/6603)

<br/>

- **문제 해석**

1-49의 수 중 k(6<k<13) 개의 수를 골라 집합 S를 만든다. 그 후 S 집합에서 6가지 수를 고를 수 있는 경우의 수를 모두 구하라. 

<br/>

- **계획**

문제에서 요구하는 것은 집합 S가 주어졌을 때 집합 S에서 6개를 골라 가능한 모든 조합을 찾는 것이다. 

조합을 찾는 과정은 다음과 같은 작은 조각으로 나눌 수 있다.

1. k 개 중 하나 고르기
2. (k-1) 개 중 하나 고르기 ...

따라서 재귀 호출을 이용해 모든 조합을 구하는 과정을 구현할 수 있다. 이때 중복되어 세어지는 것을 대비해 임의로 순서를 부여했다.

<br/>

- **제한 조건 확인**

모든 답을 생성해 가며 답의 수를 세는 재귀 호출 알고리즘은 답의 수에 정비례하는 시간이 걸린다. 따라서 시간제한 안에 수행 가능한지 확인하기 위해서는 가장 많은 경우의 수가 나올 때를 생각하면 된다. 문제에서 가장 많은 경우의 수가 나오는 경우는 k의 값이 12일 때다. 이때 나오는 경우의 수는 12!/6!6!이므로 충분히 제한 시간 안에 수행 가능하다. 

<br/>

- **내 소스 코드**

```c++
#include <iostream>
#include <vector>
using namespace std;
#define MAX 12
int k;
int s[MAX + 1];
bool check[MAX + 1];
void PrintCombination(vector<int>& combination){
    for(int i = 0; i < combination.size(); ++i) {
        cout << combination[i] << ((i == combination.size()-1) ? "\n" : " ");
    }
}
void RecursiveCombination(vector<int>& combination, int start){
    if(combination.size() == 6){
        PrintCombination((combination));
        return;
    }
    for(int i=start; i<k; ++i){
        if(!check[i]){
            check[i] = true;
            combination.push_back(s[i]);
            RecursiveCombination(combination, i+1);
            check[i] = false;
            combination.pop_back();
        }
    }
}
int main()
{
    k = -1;
    while(true){
        cin >> k;
        if(k == 0)
            break;
        for(int i=0; i<k; ++i) {
            cin >> s[i];
            check[i] = false;
        }
        vector<int> combination;
        RecursiveCombination(combination, 0);
        combination.clear();
        cout << "\n";
    }
    return 0;
}
```

<br/>

- **개선할 점**

재귀 호출 알고리즘 시간 복잡도 구하는 법 공부하기.

