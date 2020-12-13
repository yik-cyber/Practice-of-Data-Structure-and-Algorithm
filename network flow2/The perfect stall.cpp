#include<bits/stdc++.h>
using namespace std;

const int N = 210, M = 210;
vector<vector<int> > edge;
int mx[N + M], my[M + N];
bool vis[N + M];
int n, m;

int dfs(int u){ //from x
    for(int i = 0; i < edge[u].size(); i++){
        int v = edge[u][i];
        if(!vis[v]){
            vis[v] = true;
            if(my[v] == -1 || dfs(my[v])){
                mx[u] = v;
                my[v] = u;
                return 1;
            }
        }
    }
    return 0;
}

int main(){
    while(scanf("%d %d", &n, &m) != EOF){
        edge.resize(n + m + 1);
        int s, x;
        for(int i = 1; i <= n; i++){
            scanf("%d", &s);
            for(int j = 1; j <= s; j++){
                scanf("%d", &x);
                edge[i].push_back(n + x);
                edge[n + x].push_back(i);
            }
        }
        int cnt = 0;
        memset(mx, -1, sizeof(mx));
        memset(my, -1, sizeof(my));
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