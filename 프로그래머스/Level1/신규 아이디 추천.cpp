#include <string>
#include <vector>

using namespace std;

string solution(string new_id) {
    
    // step 1
    int diff = 'a' - 'A';
    for(int i=0; i<new_id.size(); ++i)
        if(new_id[i] >= 'A' && new_id[i] <= 'Z')
            new_id[i] = new_id[i] + diff;
    
    // step 2
    vector<char> after_step2;
    for(int i=0; i<new_id.size(); ++i){
        if('a' <= new_id[i] && new_id[i] <= 'z')
            after_step2.push_back(new_id[i]);
        else if('0' <= new_id[i] && new_id[i] <='9')
            after_step2.push_back(new_id[i]);
        else if(new_id[i] == '-' || new_id[i] == '_' || new_id[i] == '.')
            after_step2.push_back(new_id[i]);
        else
            continue;
    }
    
    // step 3
    vector<char> after_step3;
    after_step3.push_back(after_step2[0]);
    for(int i=1; i<after_step2.size(); ++i){
        if(after_step2[i] == '.' && after_step2[i-1] == '.')
            continue;
        else
            after_step3.push_back(after_step2[i]);
    }
    
    // step 4
    vector<char> after_step4;
    if(after_step3[after_step3.size()-1] == '.')
        after_step3.pop_back();
    for(int i=0; i<after_step3.size(); ++i){
        if(i == 0)
            if(after_step3[i] == '.')
                continue;
        after_step4.push_back(after_step3[i]);
    }
    
    // step 5
    vector<char> after_step5;
    if(after_step4.size() == 0)
        after_step5.push_back('a');
    else{
        after_step5.resize(after_step4.size());
        copy(after_step4.begin(), after_step4.end(), after_step5.begin());
    }
    
    // step 6
    if(after_step5.size() >= 16){
        while(after_step5.size() >= 16)
            after_step5.pop_back();
        if(after_step5[14] == '.')
            after_step5.pop_back();
    }
    
    // step 7
    if(after_step5.size() <= 2)
        while(after_step5.size() <= 2)
            after_step5.push_back(after_step5[after_step5.size() - 1]);
        
        
    string answer(after_step5.begin(), after_step5.end());
    return answer;
}
