#include<bits/stdc++.h>
using namespace std;
const int N = 100000 + 10;
int dfn[N], low[N], colored[N], st[N], rd[N];
bool vis[N];
int top, dep, colorn;
vector<vector<int> > edge;
vector<vector<int> > new_edge;
queue<int> nq;

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
	if(low[u] == dfn[u]){
		colorn++;
		do{
			v = st[top--];
			vis[v] = false;
			colored[v] = colorn;
		}while(v != u);
	}
}
void init(){
	memset(dfn, 0, sizeof(dfn));
	memset(low, 0, sizeof(low));
	memset(colored, 0, sizeof(colored));
	memset(rd, 0, sizeof(rd));
	memset(vis, false, sizeof(vis));
	edge.clear();
	new_edge.clear();
	top = -1;
	dep = colorn = 0;
}
int n, m, t;
int main(){
	scanf("%d", &t);
	while(t--){
		init();
		scanf("%d %d", &n, &m);
		edge.resize(n + 1);
		int x, y;
		for(int i = 1; i <= m; i++){
			scanf("%d %d", &x, &y);
			edge[x].push_back(y);
		}
		for(int i = 1; i <= n; i++){
			if(!dfn[i]) tarjan(i);
		}
		if(colorn == 1){
			printf("Strong\n");
			goto End;
		}
		new_edge.resize(colorn + 1);
		for(int i = 1; i <= n; i++){
			for(int j = 0; j < edge[i].size(); j++){
				int v = edge[i][j];
				if(colored[i] != colored[v]){
					new_edge[colored[i]].push_back(colored[v]);
					rd[colored[v]]++;
				}
			}
		}
		while(!nq.empty()) nq.pop();
		for(int i = 1; i <= colorn; i++){
			if(!rd[i]) nq.push(i);
		}
		while(!nq.empty()){
			if(nq.size() > 1){
				printf("Error\n");
				goto End;
			}
			int u = nq.front();
			nq.pop();
			
			for(int i = 0; i < new_edge[u].size(); i++){
				int v = new_edge[u][i];
				rd[v]--;
				if(!rd[v]) nq.push(v);
			}
		}
		printf("Weak\n");
		End:;
	}
}
