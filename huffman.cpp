#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

struct Node
{
    int freq;
    vector<char> children;
    Node(int f=0):freq(f) {}
};

Node operator+(const Node& lhs, const Node& rhs)
{
//    cout << "creating temporary with "<<lhs.freq << " and "<< rhs.freq<<"\n";
    Node tmp(lhs.freq + rhs.freq);
    tmp.children.reserve(lhs.children.size()+rhs.children.size());
    tmp.children.insert(tmp.children.end(), lhs.children.begin(), lhs.children.end());
    tmp.children.insert(tmp.children.end(), rhs.children.begin(), rhs.children.end());
    return tmp;
}
struct Order
{
    bool operator()(const Node& lhs, const Node& rhs)
    {
        return lhs.freq > rhs.freq;
    }
};

typedef vector<bool> Code;
const int CHARMAX = 256;
int characters[CHARMAX];
Code codes[CHARMAX];

void print()
{
    for(size_t i=0; i< CHARMAX; i++)
    {
        int j = codes[i].size();
        if(j==0) continue;
        cout <<static_cast<char>(i)<< ": ";
        for( ;j>0; --j)
        {
            cout << codes[i].back();
            codes[i].pop_back();
        }
        cout << "\n";
    }
}

void extract_encode(Node& n, bool c)
{
    for(vector<char>::iterator it= n.children.begin(); it!=n.children.end(); ++it)
        codes[static_cast<int>(*it)].push_back(c);
}

void huffman()
{
    vector<Node> v;
    for(int i=0; i< CHARMAX; ++i)
    {
        if(!characters[i])continue;
        Node tmp = Node(characters[i]);
        tmp.children.push_back(i);
        v.push_back(tmp);
    }

    Node t1, t2;
    make_heap(v.begin(), v.end(), Order());
    while(v.size()>1)
    {
        t1 = v.front();
        extract_encode(t1,0);
        pop_heap(v.begin(), v.end(), Order());
        v.pop_back();

        t2 = v.front();
        extract_encode(t2,1);
        pop_heap(v.begin(), v.end(), Order());
        v.pop_back();

        v.push_back(t1+t2);
        push_heap(v.begin(), v.end(),Order());
    }
    print();
}



void readTxt(const char* filepath)
{
    ifstream handle(filepath);
    int ct=0;
    for(char c; handle>>c;++ct)
        characters[static_cast<int>(c)]+=1;
    cout << "total chars: "<< ct <<"\n";
}

int main()
{
    //You have to provide a ascii-text file for testing its functionality
    readTxt("test.txt");
    huffman();
}
