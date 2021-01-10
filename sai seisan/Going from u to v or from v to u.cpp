#include<bits/stdc++.h>
using namespace std;
const int N = 1000 + 10;
int low[N], dfn[N], colored[N], rd[N], st[N];
bool vis[N];
int dep, top = 1, colorn;
vector<vector<int> > edge;
vector<vector<int> > cedge;
queue<int> nq;
void init(){
	memset(low, 0, sizeof(low));
	memset(dfn, 0, sizeof(dfn));
	memset(colored, 0, sizeof(colored));
	memset(rd, 0, sizeof(rd));
	memset(vis, 0, sizeof(vis));
	dep = colorn = 0;
	top = -1;
	edge.clear();
	cedge.clear();
}

void tarjan(int u){
	low[u] = dfn[u] = ++dep;
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
		}while(v != u);
	}
}
int t, n, m;
int main(){
	scanf("%d", &t);
	while(t--){
		init();
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
			printf("Yes\n");
			goto End;
		}
		cedge.resize(colorn + 1);
		while(!nq.empty()) nq.pop();
		for(int i = 1; i <= n; i++){
			for(int j = 0; j < edge[i].size(); j++){
				x = edge[i][j];
				if(colored[x] != colored[i]){
					rd[colored[x]]++;
					cedge[colored[i]].push_back(colored[x]);
				}
			}
		}
		for(int i = 1; i <= colorn; i++){
			if(!rd[i]) nq.push(i);
		}
		memset(vis, 0, sizeof(vis));
		while(!nq.empty()){
			if(nq.size() > 1){
				printf("No\n");
				goto End;
			}
			x = nq.front();
			vis[x] = true;
			nq.pop();
			
			for(int i = 0; i < cedge[x].size(); i++){
				y = cedge[x][i];
				rd[y]--;
				if(!rd[y]){
					if(!vis[y]) nq.push(y);
				}
			}
		}
		printf("Yes\n");
		End:;
	}
	
}
