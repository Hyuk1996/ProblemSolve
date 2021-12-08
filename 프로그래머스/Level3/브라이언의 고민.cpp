#include <string>
#include <unordered_map>
#include <vector>
#include <iostream>

using namespace std;

// 전역 변수를 정의할 경우 함수 내에 초기화 코드를 꼭 작성해주세요.

void appendWord(string& s, int start, int end, string& answer) {
    for(int i=start; i<=end; ++i) {
        if('A' <= s[i] && s[i] <= 'Z') {
            answer += s[i];
        }
    }
    answer += " ";
    return;
}
string solution(string sentence) {
    const string invalid = "invalid";
    
    unordered_map<char, vector<int>> dict;
    vector<char> order; // 소문자가 나오는 순서.
    vector<bool> check(26, 0);
    // sentence를 선형 탐색하면서, 소문자 위치, 개수 정보와 공백 여부 확인하기.
    for(int i=0; i<sentence.size(); ++i) {
        if(sentence[i] == ' ')
            return invalid;
        
        if('a' <= sentence[i] && sentence[i] <= 'z') {
            dict[sentence[i]].push_back(i);
            if(!check[sentence[i] - 'a']) {
                check[sentence[i] - 'a'] = true;
                order.push_back(sentence[i]);
            }   
        }
    }
    
    
    int rule;
    int curIndex = 0;
    int prevWordStart = -1;
    int prevWordEnd = -1;
    int curWordStart = 0;
    int curWordEnd = 0;
    int prevCharStart = -1;
    int prevCharEnd = -1;
    int curCharStart = 0;
    int curCharEnd = 0;
    string answer = "";
    
    // 소문자가 등장한 순서대로 적절성 판단 시작.
    for(char c : order) { 
        unordered_map<char, vector<int>>::iterator it = dict.find(c);
        
        curCharStart = it->second[0];
        curCharEnd = it->second[it->second.size() - 1];
        
        // 어떤 규칙이 적용되었는지 판단.
        // 소문자 개수 1 or 3이상 : Rule 1, 소문자 개수 2 and 포함된 문자가 2개 이상: Rule2
        // 소문자 개수 2 and 포함된 문자가 1개: Rule1 or Rule2 그런데 (aAbBbCa)와 같은 경우를 제외하고는 Rule 2 
        if(it->second.size() == 1 || it->second.size() >= 3) {
            for(int i=0; i<it->second.size()-1; ++i) {
                if(it->second[i+1] - it->second[i] != 2)
                    return invalid;
            }
            rule = 1;
        }
        else if(it->second.size() == 2) {
            if(it->second[1] - it->second[0] == 2 && (prevCharStart < curCharStart && curCharEnd < prevCharEnd)) {
                rule = 1;
            }
            else if(it->second[1] - it->second[0] >= 2) {
                rule = 2;
            }
            else
                return invalid;
        }
        
        // rule 단어별로 잘 적용되었는지 확인.
        if(rule == 1) {
            curWordStart = curCharStart - 1;
            curWordEnd = curCharEnd + 1;
            // 범위 확인.
            if(curWordStart < 0 || curWordEnd >= sentence.size())
                return invalid;
            
            // 한 단어에 같은 rule 중복 적용 불가, 단 rule1, rule2는 동시에 적용가능.
            if(prevWordStart < curWordStart && curWordEnd < prevWordEnd) {
                if(curCharStart - prevCharStart == 2 && prevCharEnd - curCharEnd == 2)
                    continue;
                else
                    return invalid;
            }
        }
        else { 
            curWordStart = curCharStart;
            curWordEnd = curCharEnd;
            
            // 단어에 rule2가 중복 적용되는 경우.
            if(prevWordStart < curWordStart && curWordEnd < prevWordEnd)
                return invalid;
        }
        
        // 단어의 구분이 잘못되어 있는 경우.
        if(prevWordEnd >= curWordStart)
            return invalid;
        
        
        // 규칙에 맞게 생성된 문구는, 정상 문구로 변환해 주기.
        if(curIndex < curWordStart) {
            appendWord(sentence, curIndex, curWordStart - 1, answer);
        }
        appendWord(sentence, curWordStart, curWordEnd, answer);
        prevWordStart = curWordStart;
        prevWordEnd = curWordEnd;
        prevCharStart = curCharStart;
        prevCharEnd = curCharEnd;
        curIndex = curWordEnd + 1;
    }
    
    if(curIndex < sentence.size()) {
        appendWord(sentence, curIndex, sentence.size() - 1, answer);
    }
    
    
    // 마지막 공백 제거.
    if(answer[answer.size() - 1] == ' ')
        answer.pop_back();
    return answer;
}
