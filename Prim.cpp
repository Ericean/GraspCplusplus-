
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <set>
#include <algorithm>
const int IFINITY = 1000000;
const int NODES = 1000000;
using namespace std;
struct Node
{
    int id;
    int dst;
    map<int,int> to;
    Node() {};
    Node(int id): id(id),dst(IFINITY) {}
    void update(int d)
    {
        dst= min(dst, d);
    }
    friend ostream& operator<<(ostream& os, const Node& n)
    {
        os<<n.id<<": "<<n.dst<<"\n";
        return os;
    }
    bool operator< (const Node& rhs)const
    {
        return dst> rhs.dst;
    }
    bool operator==(const Node& rhs)const
    {
        return id == rhs.id;
    }
};


void Prim(vector<Node>& s, int origin)
{
    vector<Node>::iterator it = find(s.begin(),s.end(),Node(origin));
    (*it).dst=0;
    make_heap(s.begin(), s.end());
    while(!s.empty())
    {
        pop_heap(s.begin(),s.end());
        Node _n= s.back();
        cout<< _n;
        s.pop_back();
        for(map<int, int>::iterator mit= _n.to.begin(); mit!= _n.to.end(); ++mit)
        {
            int t =(*mit).first, w= (*mit).second;
            vector<Node>::iterator it= find(s.begin(), s.end(),Node(t));
            (*it).update(w+_n.dst);
        }
        make_heap(s.begin(), s.end());
    }
}


int main()
{
    //for local variable, only members of class type are initialized
    //for performance concern in rare cases
    vector<Node> s;
    int nodes, edges;
    cin>> nodes >> edges;
    for(int i=1; i<=nodes; i++)
        s.push_back(Node(i));
    for(int i=1; i<edges; ++i)
    {
        int from, to, weight;
        cin >> from >>to >>weight;
        s[from-1].to.insert(make_pair(to, weight));
    }
    Prim(s, 1);
    while(!s.empty())
    {
        pop_heap(s.begin(),s.end());
        Node _n= s.back();
        cout<< _n;
        s.pop_back();
    }
    cout << "\n";
    return 0;
}


