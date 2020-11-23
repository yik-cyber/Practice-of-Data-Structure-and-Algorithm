#include<bits/stdc++.h>
using namespace std;

const int N = 105;
const int E = 2 * N * N;
int n, m, g;
double s;
struct Edge{
    public:
    int b, next;
    double r, c;
}edges[E];
int head[N];
double dis[N];
int updatetimes[N];

int cnt = 0;
void add_edge(int u, int v, double rate, double comission){
    cnt++;
    edges[cnt].b = v;
    edges[cnt].r = rate, edges[cnt].c = comission;
    edges[cnt].next = head[u];
    head[u] = cnt;
}

bool spf(){
    memset(dis, 0, sizeof(dis));
    memset(updatetimes, 0, sizeof(updatetimes));
    dis[g] = s;
    queue<int> nq;
    nq.push(g);
    int u, v;
    double r, c;
    while(!nq.empty()){
        u = nq.front();
        nq.pop();
        for(int i = head[u]; i != -1; i = edges[i].next){
            v = edges[i].b; r = edges[i].r; c = edges[i].c;
            if(!dis[u]) continue;
            double t = (dis[u] - c) * r;
            if(t > dis[v]){
                dis[v] = t;
                updatetimes[v]++;
                nq.push(v);
                if(updatetimes[v] >= n) return true;
            }
        }

    }
    return false;
}

int main(){
    memset(head, -1, sizeof(head));
    scanf("%d %d %d %lf", &n, &m, &g, &s);
    int a, b; double c1, c2, r1, r2;
    for(int i = 0; i < m; i++){
        scanf("%d %d %lf %lf %lf %lf", &a, &b, &r1, &c1, &r2, &c2);
        add_edge(a, b, r1, c1);
        add_edge(b, a, r2, c2);
    }
    if(spf()) printf("YES\n");
    else printf("NO\n");
    return 0;
}
