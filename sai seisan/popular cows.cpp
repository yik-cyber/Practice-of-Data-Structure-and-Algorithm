#include<bits/stdc++.h>
using namespace std;
const int N = 10000 + 10;
int low[N], dfn[N], colored[N], cd[N], st[N], num[N];
bool vis[N];
int dep, top = -1, colorn;
vector<vector<int> > edge;
void tarjan(int u){
	dfn[u] = low[u] = ++dep;
	st[++top] = u;
	vis[u] = true;
	int v;
	for(int i = 0; i < edge[u].size(); i++){
		v = edge[u][i];
		if(!dfn[v]){
			tarjan(v);
			low[u] = min(low[u], low[v]);
		}
		else if(vis[v]) low[u] = min(low[u], dfn[v]);
	}
	if(low[u] == dfn[u]){
		colorn++;
		do{
			v = st[top--];
			vis[v] = false;
			colored[v] = colorn;
			num[colorn]++;
		}while(v != u);
	}
}
int n, m;
int main(){
	scanf("%d %d", &n, &m);
	edge.resize(n + 1);
	int x, y;
	for(int i = 0; i < m; i++){
		scanf("%d %d", &x, &y);
		edge[x].push_back(y);
	}
	for(int i = 1; i <= n; i++){
		if(!dfn[i]) tarjan(i);
	}
	if(colorn == 1){
		printf("%d", n);
		exit(0);
	}
	for(int i = 1; i <= n; i++){
		for(int j = 0; j < edge[i].size(); j++){
			x = edge[i][j];
			if(colored[x] != colored[i]){
				cd[colored[i]]++;
			}
		}
	}
	int ans = 0, pos = 0;
	for(int i = 1; i <= colorn; i++){
		if(!cd[i]){
			ans++;
			//printf("%d", ans);
			
			if(ans > 1){
				printf("0");
				exit(0);
			}
			pos = i;
		} 
	}
	printf("%d", num[pos]);
}
