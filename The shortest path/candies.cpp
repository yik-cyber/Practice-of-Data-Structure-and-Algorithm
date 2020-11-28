#include<iostream>
#include<algorithm>
#include<cstring>
#include<vector>
#include<queue>
using namespace std;

const int N = 30000 + 10;
struct Edge{
    public:
    int v, w;
};
bool operator<(Edge a, Edge b){
    return a.w > b.w;
}
vector<vector<Edge> > edge;
bool vis[N];
int n, m;
int dijkstra(){
    priority_queue<Edge> nq;
    Edge t, s, k;
    t.v = 1;
    t.w = 0;
    nq.push(t);
    while(!nq.empty()){
        t = nq.top();
        nq.pop();

        if(vis[t.v]) continue;
        vis[t.v] = true;

        if(t.v == n){
            return t.w;
        }

        for(int i = 0 ; i < edge[t.v].size(); i++){
            s = edge[t.v][i];
            if(vis[s.v]) continue;
            k.v = s.v;
            k.w = s.w + t.w;
            nq.push(k);
        }
    }
}


int main(){
    scanf("%d %d", &n, &m);
    edge.clear();
    edge.resize(n + 1);
    int x, y, w;
    Edge t;
    while(m--){
        scanf("%d %d %d", &x, &y, &w);
        t.v = y; t.w = w;
        edge[x].push_back(t);
    }
    int ans = dijkstra();
    printf("%d", ans);
}