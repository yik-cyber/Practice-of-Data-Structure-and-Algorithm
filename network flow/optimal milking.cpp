#include<bits/stdc++.h>
using namespace std;

int k, c, m, tot, ntot;
const int K = 32, C = 202, M = 15;
const int TOT = K + C;
const int INF = 2e8;
int path[TOT][TOT];
int g[TOT][TOT];
int dis[TOT][TOT];
int layer[TOT];
bool vis[TOT];

void floyd(){ //find the shortest path between two point
    memset(dis, 0x3f3f3f3f, sizeof(dis));
    int i, j, l;
    for(i = 1; i <= tot; i++){
        for(j = 1; j <= tot; j++){
            if(path[i][j]) dis[i][j] = path[i][j];
        }
    }
    for(l = 1; l <= tot; l++){
        for(i = 1; i <= tot; i++){
            for(j = 1; j <= tot; j++){
                dis[i][j] = min(dis[i][j], dis[i][l] + dis[l][j]);
            }
        }
    }
}

bool count_layer(){
    memset(layer, 0xff, sizeof(layer));
    layer[0] = 0;
    deque<int> nq;
    nq.push_back(0);
    while(!nq.empty()){
        int v = nq.front();
        nq.pop_front();

        for(int i = 1; i <= ntot; i++){
            if(g[v][i] > 0 && layer[i] == -1){
                layer[i] = layer[v] + 1;
                if(i == ntot) return true;
                else nq.push_back(i);
            }
        }
    }
    return false;
}

int dinic(){
    int nMaxFlow = 0;
    int i, s;
    deque<int> st;
    while(count_layer()){
        memset(vis, false, sizeof(vis));
        vis[0] = true;
        st.push_back(0);

        while(!st.empty()){
            int nd = st.back();

            if(nd == ntot){
                int nMinc = INF;
                int nMinc_vs;
                for(i = 1; i < st.size(); i++){
                    int vs = st[i-1];
                    int ve = st[i];

                    if(g[vs][ve] < nMinc){
                        nMinc = g[vs][ve];
                        nMinc_vs = vs; //the last one
                    }
                }
                nMaxFlow += nMinc;
                for(i = 1; i < st.size(); i++){
                    int vs = st[i-1];
                    int ve = st[i];

                    g[vs][ve] -= nMinc;
                    g[ve][vs] += nMinc;
                }
                while (!st.empty() && st.back() != nMinc_vs){
                    vis[st.back()] = false;
                    st.pop_back();
                }
                
            }
            else{
                for(i = 1; i <= ntot; i++){
                    if(g[nd][i] > 0 && !vis[i] && layer[i] == layer[nd] + 1){
                        vis[i] = true;
                        st.push_back(i);
                        break;
                    }
                }
                if(i > ntot) st.pop_back();
            }
        }
    }
    return nMaxFlow;
}

bool check(int max_dis){
    memset(g, 0, sizeof(g));
    int i, j;
    for(i = k + 1; i <= tot; i++){
        for(j = 1; j <= k; j++){
            if(dis[i][j] <= max_dis) g[i][j] = 1; //cow flow
        }
    }
    for(i = k + 1; i <= tot; i++){
        g[0][i] = 1;
    }
    for(i = 1; i <= k; i++){
        g[i][ntot] = m;
    }
    if(dinic() == c) return true;
    else return false;
}

int main(){
    scanf("%d %d %d", &k, &c, &m);
    tot = k + c; ntot = tot + 1;
    int i, j, maxl = 0;
    for(i = 1; i <= tot; i++){
        for(j = 1; j <= tot; j++){
            scanf("%d", &path[i][j]);
            maxl += path[i][j];
        }
    }
    floyd();
    int l = 1, r = maxl, mid;
    while(l < r){
        mid = (l + r) >> 1;
        if(check(mid)) r = mid;
        else l = mid + 1;
    }
    printf("%d", r);
}