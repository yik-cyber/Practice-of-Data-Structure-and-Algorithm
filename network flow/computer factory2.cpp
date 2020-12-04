#include<bits/stdc++.h>
using namespace std;

int n, m, mp;// n tools and m factorieds
const int M = 110; //every factory divided into 2 point
const int INF = 2e8;
int g[M][M];
int layer[M];
int copy_g[M][M];
bool vis[M];
struct Fac{
    public:
    int contain;
    int in[11];
    int out[11]; //specific tools
}fac[55];

bool can_cnnt(Fac& f1, Fac& f2){
    for(int k = 1; k <= n; k++){
        if(f1.out[k] != 2 && f2.in[k] != 2 && f1.out[k] != f2.in[k]){
            return false;
        }
    }
    return true;
}

bool count_layer(){
    memset(layer, 0xff, sizeof(layer));
    layer[0] = 0;
    queue<int> nq;
    nq.push(0);
    while(!nq.empty()){
        int v = nq.front();
        nq.pop();

        for(int i = 1; i <= mp; i++){
            if(g[v][i] > 0 && layer[i] == -1){
                layer[i] = layer[v] + 1;
                if(i == mp) return true;
                else nq.push(i);
            }
        }
    }
    return false;
}

int dinic(){
    int i, s;
    int nMaxFlow = 0;
    deque<int> st;
    while(count_layer()){ //loop until count error
        memset(vis, false, sizeof(vis));
        vis[0] = true;
        st.push_back(0);

        while(!st.empty()){
            int nd = st.back();

            if(nd == mp){
                int nMinc = INF;
                int nMinc_vs;
                for(i = 1; i < st.size(); i++){
                    int vs = st[i-1];
                    int ve = st[i];
                    if(g[vs][ve] < nMinc){
                        nMinc = g[vs][ve];
                        nMinc_vs = vs;
                    }
                }
                nMaxFlow += nMinc;
                for(i = 1; i < st.size(); i++){
                    int vs = st[i-1];
                    int ve = st[i];
                    g[vs][ve] -= nMinc;
                    g[ve][vs] += nMinc;
                }
                while(!st.empty() && st.back() != nMinc_vs){
                    vis[st.back()] = false;
                    st.pop_back();
                }
            }
            else{
                for(i = 0; i <= mp; i++){
                    if(g[nd][i] > 0 &&layer[i] == layer[nd] + 1 && !vis[i]){
                        vis[i] = true;
                        st.push_back(i); // add to the path
                        break; //only one route
                    }
                }
                if(i > mp){
                    st.pop_back(); //not include nd
                }
            }
        }
    }
    return nMaxFlow;
}

int main(){
    while(scanf("%d %d", &n, &m) != EOF){
        int i, j;
        memset(g, 0, sizeof(g));
        for(i = 1; i <= m; i++){
            scanf("%d", &fac[i].contain);
            for(j = 1; j <= n; j++) scanf("%d", &fac[i].in[j]);
            for(j = 1; j <= n; j++) scanf("%d", &fac[i].out[j]);
            g[i][i+m] = fac[i].contain; //edge
        }

        //set the initial point and end point
        bool flag;
        mp = m << 1 | 1;
        int end = mp;
        for(i = 1; i <= m; i++){
            flag = true;
            for(j = 1; j <= n; j++){
                if(fac[i].in[j] == 1){
                    flag = false;
                    break;
                }
            }
            if(flag){
                g[0][i] = INF; //connect init-p to the i-th point
            }
            flag = true;
            for(j = 1; j <= n; j++){
                if(!fac[i].out[j]){
                    flag = false;
                    break;
                }
            }
            if(flag){
                g[i+m][end] = INF; //connect (i+m)-th point to the end point
            }

        }

        //set the edges between two fac
        for(i = 1; i <= m; i++){
            for(j = i + 1; j <= m; j++){
                if(can_cnnt(fac[i], fac[j])){
                    g[i+m][j] = INF; //connect tow fac
                }
                if(can_cnnt(fac[j], fac[i])){
                    g[j+m][i] = INF;
                }
            }
        }

        //copy the original graph
        memcpy(copy_g, g, sizeof(g));
        int sum = dinic();
        int cnt = 0;
        for(i = m + 1; i < mp; i++){
            for(j = 1; j <= m; j++){
                if(g[i][j] < copy_g[i][j]){
                    cnt++;
                }
            }
        }
        printf("%d %d\n", sum, cnt);
        if(cnt){
            for(i = m + 1; i < mp; i++){
                for(j = 1; j <= m; j++){
                    if(g[i][j] < copy_g[i][j]){
                        printf("%d %d %d\n", i - m, j, copy_g[i][j] - g[i][j]);
                    }
                }
            }
        }
    }
}