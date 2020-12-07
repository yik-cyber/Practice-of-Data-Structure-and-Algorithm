#include<bits/stdc++.h>
using namespace std;
const int N = 1000 + 10;
const int M = 10000 + 10;
const int INF = 2147483647;
struct Edge{
    public:
    int from, to, flow, cost, next;
}edge[M << 2];
int cnt = -1;
int head[N];
void add_edge(int u, int v, int f, int w){
    cnt++;
    edge[cnt].from = u;
    edge[cnt].to = v;
    edge[cnt].flow = f;
    edge[cnt].cost = w;
    edge[cnt].next = head[u];
    head[u] = cnt;
    
    cnt++;
    edge[cnt].from = v;
    edge[cnt].to = u;
    edge[cnt].flow = 0;
    edge[cnt].cost = -w;
    edge[cnt].next = head[v];
    head[v] = cnt;
    
    return;
}
int dis[N], flow[N], last[N];
bool vis[N];
int n, m;

bool spfa(){
    memset(dis, 127, sizeof(dis));
    memset(vis, false, sizeof(vis));
    memset(flow, 0, sizeof(flow));
    memset(last, -1, sizeof(last));
    dis[0] = 0, flow[0] = INF; vis[0] = true;
    queue<int> q;
    q.push(0);
    while(!q.empty()){
        int u = q.front();
        q.pop();
        vis[u] = false;

        for(int i = head[u]; i != -1; i = edge[i].next){
            int v = edge[i].to;
            if(edge[i].flow > 0 && dis[u] + edge[i].cost < dis[v]){
                dis[v] = dis[u] + edge[i].cost;
                last[v] = i;
                flow[v] = min(flow[u], edge[i].flow);
                if(!vis[v]){
                    vis[v] = true;
                    q.push(v);
                }
            }
        }
    }
    return (last[n+1] != -1);
}
int mfmc(){
    int sum = 0;
	while (spfa())
	{
		int now=n+1;
		int lastu=last[now];
		while (now!=0)
		{
			edge[lastu].flow-=flow[n+1];
			edge[lastu^1].flow+=flow[n+1];
			now=edge[lastu].from;
			lastu=last[now];
		}
		sum+=dis[n+1]*flow[n+1];//累计花费
	}
    return sum;
}

int main(){
    scanf("%d %d", &n, &m);
    int x, y, w;
    memset(head, -1, sizeof(head));
    for(int i = 1; i <= m; i++){
        scanf("%d %d %d", &x, &y, &w);
        add_edge(x, y, 1, w);
        add_edge(y, x, 1, w);
    }
    add_edge(0, 1, 2, 0);
    add_edge(n, n + 1, 2, 0);
    int ans = mfmc();
    printf("%d", ans);
}