#include <string>
#include <vector>

using namespace std;

string solution(int a, int b) {
    int month[] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    string days[] = {"FRI", "SAT", "SUN", "MON", "TUE", "WED", "THU"};
    string answer = "";
    
    int day_cnt = 0;
    for(int i=0; i < a - 1; ++i)
        day_cnt += month[i];
    day_cnt += b - 1;
    int day = day_cnt % 7;
    answer = days[day];

    return answer;
}
