#include<bits/stdc++.h>
using namespace std;
const int N = 10000 + 10;
const int INF = (1 << 31) - 1;
int dis[N], update[N];
bool vis[N];
struct Node{
	public:
		int v, w;
}; 
vector<vector<Node> > edge;
int n, m, t;
bool spfa(int s){
	memset(vis, 0, sizeof(vis));
	memset(update, 0, sizeof(update));
	for(int i = 1; i <= n; i++) dis[i] = INF;
	dis[s] = 0;
	queue<int> nq;
	nq.push(s);
	
	while(!nq.empty()){
		int u = nq.front();
		nq.pop();
		vis[u] = false;
		
		for(int i = 0; i < edge[u].size(); i++){
			Node e = edge[u][i];
			int v = e.v, w = e.w;
			if(dis[v] > dis[u] + w){
				dis[v] = dis[u] + w;
				update[v]++;
				if(update[v] >= n) return false;
				if(!vis[v]){
					nq.push(v);
					vis[v] = true;
				}
			}
		}
	}
	return true;
}
int s;
int main(){
	scanf("%d", &t);
	while(t--){
		scanf("%d %d %d", &n, &m, &s);
		edge.resize(n + 1);
		Node e;
		int x, y, w;
		for(int i = 0; i < m; i++){
			scanf("%d %d %d", &x, &y, &w);
			e.v = y;
			e.w = w;
			edge[x].push_back(e);
		}
		if(spfa(s)){
			for(int i = 1; i <= n; i++){
				if(dis[i] != INF){
					printf("%d ", dis[i]);
				}
				else printf("null ");
			}
		}
		else printf("Error");
		printf("\n");
		edge.clear();
	}
}
