#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
const int IFINITY = 1000000;
struct Node
{
    int id;
    double dst;
    Node(int id): id(id) {}
    Node(int id, double dst): id(id),dst(dst) {}
    friend ostream& operator<<(ostream& os, const Node& n){os<<"0 -> "<< (n.id)<<": "<<n.dst<<"\n";  return os;    }
};
bool inline operator ==(const Node& lhs, const Node& rhs) {return lhs.id ==  rhs.id;}
struct Order
{
    bool inline operator()(const Node& lhs,const Node& rhs) const
    {
        return lhs.dst> rhs.dst;
    }
};
typedef pair<int,double> Edge;
typedef vector<vector<pair<int,double> > > Graph;


void dijkstra(Graph& g, int src)
{
    vector<Node> s;
    vector<bool> marked(g.size());
    //find src's neighbors, and then push them into the heap;
    marked[src]= true;
    vector<Edge>::iterator it= g[src].begin();
    for(; it!= g[src].end(); ++it)
        s.push_back(Node((*it).first,(*it).second));
    //make the heap
    make_heap(s.begin(),s.end(),Order());
    //do computation while inserting
    //check explored set simultaneously
    while(!s.empty())
    {
        pop_heap(s.begin(),s.end(),Order());
        Node _n= s.back();
        int t = _n.id;
        double min_dist= _n.dst;
        marked[t]=true;
        cout<< _n;
        s.pop_back();

        for(it= g[t].begin(); it!=g[t].end(); ++it)
        {
            int nt = (*it).first;
            double nd= (*it).second;
            vector<Node>::iterator vit = find(s.begin(),s.end(),Node(nt));
            if(vit!=s.end())
                (*vit).dst = min(min_dist+nd, (*vit).dst);
            else if(!marked[nt])
                s.push_back(Node(nt, min_dist+nd));
        }
        //adjustify the order once we mess the key
        //a lazy version of readjusting the order
        //incuring overhead due to the sole use of stl
        make_heap(s.begin(),s.end(),Order());
    }
}


//refet to http://algs4.cs.princeton.edu/44sp/ for testing data set
int main()
{
    int nodes, edges;
    cin>> nodes >> edges;
    Graph adj(nodes,vector<Edge>());
    for(int i=0; i<edges; ++i)
    {
        int from, to;
        double weight;
        cin >> from >>to >>weight;
        adj[from].push_back(make_pair(to, weight));
    }
    dijkstra(adj, 0);
    return 0;
}


