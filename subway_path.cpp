#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
class Foo{
public:
    int a;
    double b;
    friend ostream& operator<<(ostream& os, const Foo& f){os<<"a: "<<f.a<<"b: "<<f.b<<endl;return os;}
};

struct Edge{
    int from,to,days;
    Edge(){}
    Edge(int from, int to, int days): from(from),to(to),days(days){}
    bool operator<(const Edge& o) const {return days< o.days;}
    friend ostream& operator<<(ostream& os, const Edge& e){ os<< e.from<<"->"<<e.to<<": "<<e.days<<endl;return os;}
};
vector<Edge> es;
vector<int> index;
int _root(int e)
{
    if(e== index[e])return e;
    index[e]= _root(index[e]);
    return index[e];
}

bool ufind(int p,int q)
{
    return _root(p)==_root(q);
}

void unite(int p, int q)
{
    int i= _root(p);
    int j= _root(q);
    index[i]= j;
}


int main()
{
    int num_stations, num_options;
    cin >> num_stations >>num_options;
    for(int i=0; i<num_options; i++){
        int f, t, d;
        cin>> f >> t >>d;
        es.push_back(Edge(f,t,d));
    }
    sort(es.begin(), es.end());
    for(int i=0; i<num_stations;i++)
        index.push_back(i);
    int i,f,t;
    for(i=0; i<num_options;i++){
            f= es[i].from;
            t= es[i].to;
        if(!ufind(f-1,t-1))
            unite(f-1,t-1);
        if(ufind(0,num_stations-1))break;
    }
    cout <<es[i].days<<endl;
    return 0;
}
