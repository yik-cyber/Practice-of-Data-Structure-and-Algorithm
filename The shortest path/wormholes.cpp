#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;

const int N = 510, M = 2510, W = 210;
struct Edge{
    public:
    int v, w;
};
vector<vector<Edge> > edge;
int dis[N];
int update[N];
const int INF = 1 << 30;
int t, n, m, s;

bool spf(int u){
    for(int i = 1; i <= n; i++){
        dis[i] = INF;
        update[i] = 0;
    }
    Edge e;
    queue<int> que;
    dis[u] = 0;
    que.push(u);
    while(!que.empty()){
        int r = que.front();
        que.pop();

        for(int i = 0; i < edge[r].size(); i++){
            e = edge[r][i];
            if(dis[r] != INF && dis[r] + e.w < dis[e.v]){
                dis[e.v] = dis[r] + e.w;
                update[e.v]++;
                que.push(e.v);
                if(update[e.v] >= n) return true;
            }
        }
    }
    return false;
    
}

int main(){
    scanf("%d", &t);
    while(t--){
        Edge e;
        scanf("%d %d %d", &n, &m, &s);
        int x, y, w;
        edge.clear();
        edge.resize(n + 1);
        for(int i = 1; i <= m; i++){
            scanf("%d %d %d", &x, &y, &w);
            e.v = y, e.w = w;
            edge[x].push_back(e);
            e.v = x;
            edge[y].push_back(e);
        }
        for(int i = 1; i <= s; i++){
            scanf("%d %d %d", &x, &y, &w);
            e.v = y, e.w = -w;
            edge[x].push_back(e);
        }
        if(spf(1)){
            printf("YES\n");
        }
        else printf("NO\n");
    }
}