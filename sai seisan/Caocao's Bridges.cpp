#include<bits/stdc++.h>
using namespace std;
const int N = 1000 + 10;
int g[N][N];
int low[N], dfn[N], fa[N];
int dep, ans;
int n, m, t;
vector<vector<int> > edge;

void init(){
	memset(g, 0xff, sizeof(g));
	memset(low, 0, sizeof(low));
	memset(dfn, 0, sizeof(dfn));
	memset(fa, 0xff, sizeof(fa));
	dep = 0;
	ans = 0x3f3f3f3f;
	edge.clear();
}
void tarjan(int u){
	low[u] = dfn[u] = ++dep;
	int v;
	for(int i = 0; i < edge[u].size(); i++){
		v = edge[u][i];
		if(!dfn[v]){
			fa[v] = u;
			tarjan(v);
			low[u] = min(low[u], low[v]);
			if(dfn[u] < low[v]){
				ans = min(ans, g[u][v]);
			}
		}
		else if(v != fa[u]) low[u] = min(low[u], dfn[v]);
	}
}

int main(){
	while(scanf("%d %d", &n, &m) && n != 0 && m != 0){
		init();
		edge.resize(n + 1);
		int x, y, w;
		for(int i = 0; i < m; i++){
			scanf("%d %d %d", &x, &y, &w);
			edge[x].push_back(y);
			edge[y].push_back(x);
			if(g[x][y] != -1){
				g[x][y] = g[y][x] = 0x3f3f3f3f;
			}
			else g[x][y] = g[y][x] = w;
		}
		fa[1] = -1;
		tarjan(1);
		for(int i = 2; i <= n; i++){
			if(!dfn[i]){
				printf("0\n");
				goto End;
		    }
		}
		if(ans == 0x3f3f3f3f){
			printf("-1\n");
		}
		else if(ans == 0){
			printf("1\n");
		}
		else{
			printf("%d\n", ans);
		}
		End:;
	}
}
