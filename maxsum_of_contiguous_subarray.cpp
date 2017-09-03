#include <iostream>
#include <vector>
using namespace std;
int main()
{
    vector<int> seq;
    int nums; cin >> nums;
    int number;
    for(int i=0;i < nums; ++i){
        cin >> number;
        seq.push_back(number);
    }
    for(int i=0;i < nums; ++i){
       cout << seq[i] <<" ";
    }
    cout << "\n";


    /* dp[i]= max{dp[i-1]+elem[i], elem[i]}
       result= max{dp[i]}} i \in [1,n] */
    int gs=0, ge=1, gmax=seq[0]; //keep track of global max history
    int ts=0, te=1, tmax= seq[0]; //keep track of local max history
    for(int i=1; i<nums; ++i)
    {
        if(tmax + seq[i] >= seq[i]){
            te +=1;
            tmax += seq[i];
        }else{
            ts = i;
            te = i+1;
            tmax = seq[i];
        }
//        cout << i <<": "<< tmax<<"\n";
        if(tmax>gmax){
            gs = ts;
            ge = te;
            gmax = tmax;
        }
    }
    //output routine
    //format: {the result sub-contiguous array}:#sum
    cout << "{";
    for(int i= gs; i<ge; i++)
        cout << seq[i] << ", ";
    cout <<"} : "<< gmax<<"\n";

}
