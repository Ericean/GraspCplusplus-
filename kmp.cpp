#include <iostream>
#include <string>
#include <vector>
using namespace std;
vector<int> compute_next(string& pattern)
{
    vector<int> rewind_pos(pattern.size(),0);
    for(size_t k=1; k<pattern.size(); ++k){
        //fetch the previous ending point of the common part(between the suffix and prefix of the matched substring)
        int i = k-1;//fetch its neighbor's pos
        int x = rewind_pos[i];
        //we have to squeeze the previous common part to find the new one
        //once the subsequent comparison fails
        while(pattern[k]!= pattern[x])
        {
            i= x-1;
            if(i<0)break;
            x= rewind_pos[i];
        }
        //otherwise we can expand current common part by including xth character
        rewind_pos[k]= (i<0)? 0 : rewind_pos[i]+1;
    }
    return rewind_pos;
}

int main()
{
    /*
    output examples;
    "if current char mismatches, then use previous rewinding_pos to align with current pointer
    note this never rewind the to-be-matched string's iterater"

    pattern : abacab
    a | b | a | c | a | b |
    0 | 0 | 1 | 0 | 1 | 2 |
    */
    string s; cin >> s;
    cout <<"pattern : "<< s <<"\n";
    vector<int> results =compute_next(s);
    for(size_t i=0; i< results.size();++i)
        cout << s[i] << " | ";
    cout << "\n";
    for(size_t i=0; i< results.size();++i)
        cout << results[i] << " | ";
    cout << "\n";
}
