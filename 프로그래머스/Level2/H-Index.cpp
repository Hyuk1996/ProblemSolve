#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

int solution(vector<int> citations) {
    int answer = 0;
    
    sort(citations.begin(), citations.end(), greater<int>());
    int citation_cnt;
    int paper_cnt = 0;
    for(int i=0; i<citations.size() - 1; i++){
        citation_cnt = citations[i];
        paper_cnt++;
        while(citation_cnt > citations[i + 1]){
            if(citation_cnt <= paper_cnt){
                answer = citation_cnt;
                return answer;
            }
            citation_cnt--;
        }
    }
    
    citation_cnt = citations[citations.size() - 1];
    paper_cnt++;
    while(citation_cnt >= 0){
        if(citation_cnt <= paper_cnt){
            answer = citation_cnt;
            break;
        }
        citation_cnt--;
    }
    return answer;
}
