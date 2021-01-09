#include<bits/stdc++.h>
using namespace std;
const int N = 80000 + 10;
vector<vector<int> > edge;
int low[N], dfn[N];
bool is_cut[N];
int dep, root_ch, cut_cnt;

void init(){
	memset(low, 0, sizeof(low));
	memset(dfn, 0, sizeof(dfn));
	memset(is_cut, 0, sizeof(is_cut));
	edge.clear();
	dep = 0;
	root_ch = 0;
	cut_cnt = 0;
}

void tarjan(int u, int f){
	dfn[u] = low[u] = ++dep;
	int v, chd = 0;
	for(int i = 0; i < edge[u].size(); i++){
		v = edge[u][i];
		if(!dfn[v]){
			tarjan(v, u);
			low[u] = min(low[u], low[v]);
			if(dfn[u] <= low[v]) chd++;
		}
		else if(f != v) low[u] = min(low[u], dfn[v]);
	}
	if(f == 0) chd--;
	if(chd >= 1){
		is_cut[u] = true;
		cut_cnt++;
	}
}
int n, m, t;
void cut_point(){
	if(cut_cnt == 0){
		printf("null\n");
		return;
	}
	bool flag = false;
	for(int i = 1; i <= n; i++){
		if(is_cut[i]){
		    if(flag) printf(" %d", i);
			else printf("%d", i);
			flag = true;	
		} 
	}
	printf("\n");
	return;
}

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
			edge[y].push_back(x);
		}
		for(int i = 1; i <= n; i++){
			if(!dfn[i]) tarjan(i, 0);
		}
		cut_point();
	}
}
