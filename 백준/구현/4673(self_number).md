# 백준 4673

[문제 출처](https://www.acmicpc.net/problem/4673)

<br/>

- **문제 해석**

셀프 넘버는 생성자가 없는 수이다. 10000보다 작거나 같은 셀프 넘버를 출력하라.

<br/>

- **계획**

무식하게 접근했다. 

문제는 10000보다 작은 셀프 넘버를 구하는 것이다. 입력의 크기가 작다. 10000개를 다 확인해도 1초라는 시간 제한 안에 충분히 가능하다고 생각했다. 그래서 1부터 10000까지의 수를 생성자로 d(n)을 구했다. 그러면 나머지 숫자들이 셀프 넘버가 된다.

<br/>

- **내 코드**

```c++
#include <iostream>
#include <algorithm>
using namespace std;
#define MAX 10000

bool self_number[MAX + 1];

int main(){
    fill_n(self_number, MAX + 1, true);
    for(int i = 1; i < MAX + 1; ++i){
        int result = i;
        int num = i;
        while ( num != 0){
            result += num % 10;
            num /= 10;
        }
        if(result <= 10000)
            self_number[result] = false;
    }
    for(int i = 1; i < MAX +1; ++i)
        if(self_number[i])
            cout << i << "\n";
    return 0;
}
```



- **개선할 부분 + 배운 부분**

fill_n 함수에 대해 알게 되었다. 

[자세한 설명](https://en.cppreference.com/w/cpp/algorithm/fill_n)