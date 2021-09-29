#include <string>
#include <algorithm>
#include <iostream>
#include <map>

using namespace std;

void getElement(string &s, map<string, int> &m){
    int diff = 'a' - 'A';
    bool flag1 = false, flag2 = false;
    for(int i=0; i<s.size(); ++i){
        if('a' <= s[i] && s[i] <= 'z'){
            s[i] = s[i] - diff;
            flag2 = true;
        }
        else if('A' <= s[i] && s[i] <= 'Z')
            flag2 = true;
        else
            flag2 = false;
        
        if(flag1 && flag2){
            string elem = s.substr(i-1, 2);
            if(m.find(elem) == m.end())
                m[elem] = 1;
            else
                m[elem]++;
        }
        
        flag1 = flag2;
    }
}
int solution(string str1, string str2) {
    int answer = 0;
    // 원소 구하기.
    map<string, int> m;
    map<string, int> m2;
    
    getElement(str1, m);
    getElement(str2, m2);
    
    
    // 자카드 유사도 구하기.
    map<string, int>::iterator iter1;
    map<string, int>::iterator iter2;
    
    int intersection = 0;
    int union_value = 0;
    
    for(iter1 = m.begin(); iter1!=m.end(); iter1++){
        iter2 = m2.find(iter1->first);
        if(iter2 == m2.end()){
             union_value += iter1->second;
        }
        else{
            intersection += min(iter1->second, iter2->second);
            union_value += max(iter1->second, iter2->second);
            m2.erase(iter2);
        }
    }
    
    for(iter1 = m2.begin(); iter1!=m2.end(); iter1++)
        union_value += iter1->second;
    
    if(union_value == 0 && intersection == 0)
        answer = 65536;
    else{
        double tmp = ((double)intersection / (double)union_value);
        answer = tmp * 65536;
    }
    
    return answer;
}
