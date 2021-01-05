#include<iostream>
#include<algorithm>
#include<vector>
#include<set>
using namespace std;

const int N = 1e4 + 10, M = 5e4 + 10;
int dfn[N], low[N], colored[N], st[N];
bool vis[N];
int color_out[N], color_pn[N];
vector<vector<int> > edge;
vector<set<int> > new_edge;
int n, m, dep, colorn, top = -1;

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
        else if(vis[v])low[u] = min(low[u], dfn[v]);
    }
    if(dfn[u] == low[u]){
        colorn++;
        do{
            v = st[top--];
            colored[v] = colorn;
            color_pn[colorn]++;
            vis[v] = false;
        }while(v != u);
    }
}
int main(){
    int x, y;
    scanf("%d %d", &n, &m);
    edge.resize(n + 1);
    for(int i = 0; i < m; i++){
        scanf("%d %d", &x, &y);
        edge[x].push_back(y);
    }
    for(int i = 1; i <= n; i++){
        if(!dfn[i]) tarjan(i);
    }
    new_edge.resize(colorn + 1);
    for(int i = 1; i <= n; i++){
        for(int j = 0; j < edge[i].size(); j++){
            int v = edge[i][j];
            if(colored[v] != colored[i]){
                new_edge[colored[i]].insert(colored[v]);
            }
        }
    }
    int flag = 0, ans = 0;
    for(int i = 1; i <= colorn; i++){
        if(new_edge[i].size() == 0){
            if(!flag){
                flag = 1;
                ans = color_pn[i];
            }
            else{
                printf("0");
                return 0;
            }
        }
    }
    if(flag) printf("%d", ans);
    else printf("0");
}
