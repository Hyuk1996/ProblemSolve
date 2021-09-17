# 백준 1152번 

[문제 정보](https://www.acmicpc.net/problem/1152)

<br/>

- **문제 해석**

입력받은 문자열의 단어 수 세기. 

<br/>

- **계획**

입력받은 문자열의 단어의 수는 공백(' ')을 세면 알 수 있다.

따라서 입력받은 문자열을 처음부터 끝까지 탐색하면서 ' '의 개수를 센다. 따라서 시간 복잡도는 O(n)이다. 이때 문자열 맨 뒤에 오는 공백은 무시하자. 그리고 문자열 앞의 공백은 카운트해준다. 하지만 마지막에 답을 출력할 때는 앞의 공백의 유무를 기준으로 알맞은 답을 출력한다.

<br/>

- 내 소스 코드

```c++
#include <iostream>
#include <cstring>
using namespace std;
#define MAX 1000000

char input_string[MAX + 1];

int main() {
    cin.getline(input_string, MAX,'\n');
    int count_word = 0;
    for(int i = 0; i < strlen(input_string); ++i){
        if(input_string[i] == ' '){
            if(i == strlen(input_string)-1)
                continue;
            ++count_word;
        }
    }

    if(input_string[0] == ' ')
        cout << count_word << "\n";
    else
        cout << count_word + 1 <<"\n";
    return 0;
}
```



- **개선할 부분**

처음에 입력이 공백 하나, 문자 하나가 입력되는 경우를 생각하지 못했다. 그래서 생각보다 시간이 걸렸다. 다음부터는 모든 경우의 수를 생각하려고 노력해야겠다. 