#include<iostream>
#include<algorithm>
#include<queue>
#include<vector>
#include<cstring>
using namespace std;

const int N = 105;
int n, m, g;
double s;
struct Edge{
    public:
    int b;
    double r, c;
};
vector<vector<Edge> > edge;
double dis[N];
int update[N];

bool spfa(){
    memset(dis, 0 ,sizeof(dis));
    memset(update, 0, sizeof(update));
    queue<int> nq;
    nq.push(g);
    dis[g] = s;
    int u, v;
    double r, c;
    while(!nq.empty()){
        u = nq.front();
        nq.pop();

        if(!dis[u]) continue;

        for(int i = 0; i < edge[u].size(); i++){
            v = edge[u][i].b;
            r = edge[u][i].r;
            c = edge[u][i].c;
            double t = r * (dis[u] - c);
            if(t > dis[v]){
                dis[v] = t;
                update[v]++;
                nq.push(v);
                if(update[v] >= n) return true;
            }
        }
    }
    return false;
}

int main(){
    scanf("%d %d %d %lf", &n, &m, &g, &s);
    int a, b;
    double r1, c1, r2, c2;
    edge.resize(n + 1);
    Edge t;
    for(int i = 0; i < m; i++){
        scanf("%d %d %lf %lf %lf %lf", &a, &b, &r1, &c1, &r2, &c2);
        t.b = b; t.r = r1; t.c = c1;
        edge[a].push_back(t);
        t.b = a; t.r = r2; t.c = c2;
        edge[b].push_back(t);
    }
    if(spfa()) printf("YES\n");
    else printf("NO\n");
}