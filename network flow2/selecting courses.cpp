#include<bits/stdc++.h>
using namespace std;

const int N = 310;
const int M = 7 * 12 + 10;
vector<vector<int> > edge;
int mx[N+M], my[N+M];
bool vis[N+M];

int dfs(int u){
    for(int i = 0; i < edge[u].size(); i++){
        int v = edge[u][i];
        if(!vis[v]){
            vis[v] = true;
            if(my[v] == -1 || dfs(my[v])){
                mx[u] = v; my[v] = u;
                return 1;
            }
        }
    }
    return 0;
}
int n;
int main(){
    while(scanf("%d", &n) != EOF){
    edge.resize(N + M + 1);
    int t, p, q, c;
    for(int i = 1; i <= n; i++){
        scanf("%d", &t);
        while(t--){
            scanf("%d %d", &p, &q);
            c = 12 * p + q;
            edge[i].push_back(n + c);
            edge[n + c].push_back(i);
        }
    }
    memset(mx, -1, sizeof(mx));
    memset(my, -1, sizeof(my));
    int cnt = 0;
    for(int i = 1; i <= n; i++){
        if(mx[i] == -1){
            memset(vis, false, sizeof(vis));
            cnt += dfs(i);
        }
    }
    printf("%d\n", cnt);  
    edge.clear();      
    }
}