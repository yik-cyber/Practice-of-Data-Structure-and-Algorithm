#include<bits/stdc++.h>
using namespace std;

int n, t;
const int N = 1001;
struct Node{
    public:
    int w, v;
};
bool operator<(Node a, Node b){
    return a.w > b.w;
}
vector<Node> edges[N];
int mp[N][N];
bool vis[N];

int dijkstra(){
    memset(vis, false, sizeof(vis));
    Node t;
    t.v = n;
    t.w = 0;
    priority_queue<Node> pq;
    pq.push(t);
    while(!pq.empty()){
        t = pq.top();
        pq.pop();

        if(vis[t.v]) continue;
        vis[t.v] = true;

        if(t.v == 1) return t.w;

        for(int i = 0; i < edges[t.v].size(); i++){
            Node q;
            q.v = edges[t.v][i].v;
            if(vis[q.v]) continue;
            q.w = t.w + edges[t.v][i].w;
            pq.push(q); 
        }
    }   
}

int main(){
    scanf("%d %d", &t, &n);
    memset(mp, 0, sizeof(mp));
    while(t--){
        int x, y, p;
        scanf("%d %d %d", &x, &y, &p);
        if(!mp[x][y] || p < mp[x][y]){
            mp[x][y] = p;
            Node t;
            t.w = p;
            t.v = y; 
            edges[x].push_back(t);
            t.v = x;
            edges[y].push_back(t);
        }
    }
    printf("%d", dijkstra());
}
