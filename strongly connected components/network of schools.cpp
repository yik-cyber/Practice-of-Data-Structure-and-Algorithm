#include<iostream>
#include<algorithm>
#include<vector>
#include<cstring>
#include<set>
using namespace std;

const int N = 105;
vector<vector<int> > edge;
int dfn[N], low[N], colored[N], st[N], rudu[N], chudu[N];
bool vis[N];
int dep, colorn, top;
void tarjan(int u){
    dfn[u] = low[u] = ++dep;
    vis[u] = true;
    st[++top] = u;
    int v;
    for(int i = 0; i < edge[u].size(); i++){
        v = edge[u][i];
        if(!dfn[v]){
            tarjan(v);
            low[u] = min(low[u], low[v]);
        }
        else if(vis[v]) low[u] = min(low[u], dfn[v]);
    }
    if(dfn[u] == low[u]){
        colorn++;
        do{
            v = st[top--];
            colored[v] = colorn;
            vis[v] = false;
        }while(v != u);
    }
}

int n;
int main(){
    memset(vis, false, sizeof(vis));
    dep = colorn = 0;
    scanf("%d", &n);
    int x;
    edge.resize(n + 1);
    for(int i = 1; i <= n; i++){
        while(scanf("%d", &x) && x != 0){
            edge[i].push_back(x);
        }
    }
    for(int i = 1; i <= n; i++){
        if(!dfn[i]) tarjan(i);
    }
    for(int i = 1; i <= n; i++){
        for(int j = 0; j < edge[i].size(); j++){
            int v = edge[i][j];
            if(colored[i] != colored[v]){
                rudu[colored[v]]++;
                chudu[colored[i]]++;
            }
        }
    }
    int max_out = 0, max_in = 0;
    for(int i = 1; i <= colorn; i++){
        if(!rudu[i]) max_out++;
        if(!chudu[i]) max_in++;
    }
    printf("%d\n", max_out);
    if(colorn == 1) printf("0");
    else printf("%d", max(max_in, max_out));
}
