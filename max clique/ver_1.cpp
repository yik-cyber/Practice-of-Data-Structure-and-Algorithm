#include<bits/stdc++.h>
using namespace std;

const int N = 760 + 5;
const int M = N * N;
const int MAX_STEP = 150;
FILE* f;
FILE* fo;
int g1[N][N], g[N][N], weight[M];
int n, k, ub, tabu_add, tabu_remove, step;

struct Edge_Val{
    public:
    int val, p;
};
Edge_Val dscore[N];
bool encmp(Edge_Val& en1, Edge_Val& en2){
    return en1.val < en2.val;
}


class Edge{
    public:
    int v[2];
    int tag;
    Edge(int _u, int _v){
        v[0] = _u; v[1] = _v;
        tag = step;
    }
    Edge(){}
}edges[M];

bool lcmp(int x, int y){ //the min tag
    return edges[x].tag < edges[y].tag;
}
int sort_array[M]; //temperary array for sort
vector<int> vertex[N];
int ecnt = 0;
void add_edge(int u, int v){
    edges[++ecnt].v[0] = u;
    edges[ecnt].v[1] = v;
    edges[ecnt].tag = step;
    weight[ecnt] = 1;
    vertex[u].push_back(v);
    vertex[v].push_back(u);
    g[u][v] = g[v][u] = ecnt;
}


int rand_int(int l, int r){
    int q = r - l + 1;
    return l + (rand() % q);
}
class C_part;
class L_part{
    public:
    int l_elem[M]; //checked
    int l_pos[M];
    int l_size;

    L_part(){
        reset();
    }
    void reset(){
        l_size = 0;
        memset(l_elem, 0, sizeof(l_elem));
        memset(l_pos, 0xff, sizeof(l_pos));
    }

    L_part& operator=(const L_part& lp){
        memcpy(l_elem, lp.l_elem, sizeof(l_elem));
        memcpy(l_pos, lp.l_pos, sizeof(l_pos));
        l_size = lp.l_size;
        return *this;
    }

    void del_elem(int e){ //delete
        int p = l_pos[e];
        l_pos[e] = -1;
        l_size--;
        if(l_size > 0&& p < l_size){
            l_elem[p] = l_elem[l_size]; //还要考虑没有元素的情况
            l_pos[l_elem[p]] = p;
        }
    }

    void add_elem(int e){
        edges[e].tag = step;
        l_elem[l_pos[e] = l_size++] = e;
    }
    void add_elem_by_vertex(int v, C_part& cp);
    void del_elem_by_vertex(int v, C_part& cp);

    void update_weight(){
        int i;
        for(i = 0; i < l_size; i++){
            weight[l_elem[i]]++;
        }
    }

    int random_edge(){
        return l_elem[rand_int(0, l_size - 1)];
    }
};


class C_part{
    public:
    int c_size;
    int c_elem[N];
    int c_pos[N];
    int cost_c;

    C_part(){
        reset();
    }
    void reset(){
        c_size = 0;
        memset(c_elem, 0, sizeof(c_elem));
        memset(c_pos, 0xff, sizeof(c_pos));
    }

    C_part& operator=(const C_part& cp){
        c_size = cp.c_size;
        memcpy(c_elem, cp.c_elem, sizeof(c_elem));
        memcpy(c_pos, cp.c_pos, sizeof(c_pos));
        return *this;
    }

    int random_elem(){ 
        assert(c_size > 0);
        int t = rand_int(0, c_size - 1);      
        return c_elem[t];
    }
    
    bool in_C(int u){
        return (c_pos[u] >= 0);
    }
    void del(int u){ //delete vertex u from C
        int p = c_pos[u];
        c_pos[u] = -1;
        c_size--;
        if(c_size > 0 && p < c_size){ //not the last elem
           c_elem[p] = c_elem[c_size]; 
           c_pos[c_elem[p]] = p;
        }

    }

    void add(int u){
        c_elem[c_pos[u] = c_size++] = u;
    }

    void update_cost(L_part& lp){
        int i;
        cost_c = 0;
        for(i = 0; i < lp.l_size; i++){
            cost_c += weight[lp.l_elem[i]];
        }
    }
    //在已经更新了cost_c的前提下对点的变动重新更新cost
    void inc_cost_by_rmv(int u){
        int i, v;
        for(i = 0; i < vertex[u].size(); i++){
            v = vertex[u][i];
            if(c_pos[v] == -1) cost_c += weight[g[u][v]];
            //将u移出C，若(u,v)的v不在C中，则(u,v)加入L，cost_c增加
        }
    }
    void dec_cost_by_adv(int u){
        int i, v;
        for(i = 0; i < vertex[u].size(); i++){
            v = vertex[u][i];
            if(c_pos[v] == -1) cost_c -= weight[g[u][v]];
            //将u加入C，若(u,v)的v不在C中，则(u,v)移出L，cost_c减少
        }
    }

    int cal_dscore(int u){
        int cost_cu = cost_c, i, v;
        if(c_pos[u] != -1){
            //u is in C, but the other point is not in C
            for(i = 0; i < vertex[u].size(); i++){
                v = vertex[u][i];
                if(c_pos[v] == -1){ //now (u, v) is in L
                    cost_cu += weight[g[u][v]];
                }
            }
        }
        else{
            //u is not in C, as listed above
            for(i = 0; i < vertex[u].size(); i++){
                v = vertex[u][i];
                if(c_pos[v] == -1){ //now (u, v) is not in L
                    cost_cu -= weight[g[u][v]];
                }
            }
        }
        return (dscore[u].val = cost_c - cost_cu); //顺便更新dscore
    }

    int cal_sore(int u, int v){
        int score = cal_dscore(u) + cal_dscore(v);
        if(g[u][v] > 0){
            //(u, v) in E
            score += weight[g[u][v]];
        }
        return score;
    }
};

void L_part::add_elem_by_vertex(int v, C_part& cp){// when remove v from C
    int u;
    for(int i = 0; i < vertex[v].size(); i++){
        u = vertex[v][i];
        if(cp.c_pos[u] == -1){
            add_elem(g[v][u]);//如果u不在C中,(u,v)加入L
        }
    }
}
void L_part::del_elem_by_vertex(int v, C_part& cp){ //move v into C
    int u;
    for(int i = 0; i < vertex[v].size(); i++){
        u = vertex[v][i];
        if(cp.c_pos[u] == -1){
            del_elem(g[v][u]); //如果u不在C中,(u,v)移出L
        }
    }
}




vector<pair<int, int> > S;

/* construct c to a vertex cover */
void construct_cp(C_part& cp, L_part& lp){
    int i, j;
    int* l_elem = lp.l_elem;
    int* c_elem = cp.c_elem;
    int* c_pos = cp.c_pos;
    cp.update_cost(lp); //update the cost(G,C)
    int max_ds_p = 0, max_ds = -2e8;
    for(i = 1; i <= n; i++){
        cp.cal_dscore(i); //update the dscore of all vertices
        if(dscore[i].val > max_ds){
            max_ds = dscore[i].val;
            max_ds_p = i; //record the current max dscore vertex
        }
    }
    if(max_ds_p > 0){
        cp.add(max_ds_p);
        cp.dec_cost_by_adv(max_ds_p);
        lp.del_elem_by_vertex(max_ds_p, cp);
    }
    while(lp.l_size > 0){
        max_ds = 0;
        max_ds = -2e8;
        for(i = 1; i <= n; i++){
            cp.cal_dscore(i);
            if(!cp.in_C(i) && dscore[i].val > max_ds){
                max_ds_p = i;
                max_ds = dscore[i].val;
            }
        }
        cp.add(max_ds_p);
        cp.dec_cost_by_adv(max_ds_p);
        lp.del_elem_by_vertex(max_ds_p, cp);
    }
}


/*remove some vertices until |C| < ub - delta*/
void random_remove_vertices(C_part& cp,L_part& lp, int delta){
    int rm_u;
    while(cp.c_size > 1 && cp.c_size >= ub - delta){
        rm_u = cp.random_elem();
        cp.del(rm_u);
        lp.add_elem_by_vertex(rm_u, cp);
    }
}

pair<int, int> choose_exchange_pair(C_part& cp,L_part& lp){
    cp.update_cost(lp);
    // calculate the scores of edges in L ?
    S.clear();
    int max_score = -2e8, ts;
    pair<int, int> max_score_pair;
    memcpy(sort_array, lp.l_elem, sizeof(int) * lp.l_size);
    sort(sort_array, sort_array + lp.l_size, lcmp);
    int i, e, v1, v2, j, u;
    for(i = 0; i < lp.l_size; i++){
        if(S.size() >= 10) break;
        e = sort_array[i];
        v1 = edges[e].v[0], v2 = edges[e].v[1];
        for(j = 0; j < cp.c_size; j += 2){
            u = cp.c_elem[j];
            //calculation of score can be optimized
            if(ts = cp.cal_sore(u, v1) > 0){
                if(ts > max_score){
                    max_score = ts;
                    max_score_pair = {u, v1};
                }
                S.push_back({u, v1});
            } 
            if(ts = cp.cal_sore(u, v2) > 0){
                if(ts > max_score){
                    max_score = ts;
                    max_score_pair = {u, v2};
                }
                S.push_back({u, v2});
            }
        }
    }
    if(S.empty()) return make_pair(0, 0);
    else return max_score_pair;
}

L_part lpp, ll;
C_part cpp, cc;
vector<int> max_cliq;
void check_mc();
void solve(){
    int i, x, y, j, m;
    step = 0;
    for(i = 1; i <= k; i++){
        scanf("%d %d", &x, &y);
        g1[x][y] = g1[y][x] = 1; //the edge mark
    }

    for(i = 1; i < n; i++){
        for(j = i + 1; j <= n; j++){
            if(g1[i][j] == 0){
                add_edge(i, j);
                lpp.add_elem(ecnt);
            }
        }
    }

    construct_cp(cpp, lpp);
    ub = cpp.c_size; cc = cpp; //debug
    int delta = min(cpp.c_size - 1, 10);
    random_remove_vertices(cpp, lpp, 0.6 * cpp.c_size);
    pair<int, int> tp;
    bool flag = true;
    while(step < MAX_STEP){
        flag = false;
        if(step == 2){
            m = 2;
        }
        while((tp = choose_exchange_pair(cpp, lpp)) != make_pair(0, 0)){
            if(!(tp.first == tabu_add && tp.second == tabu_remove)){
                flag = true;
                break;
            }
        }
        if(flag){
            tabu_add = tp.first; //u in C 
            tabu_remove = tp.second; //v not in C
            cpp.del(tabu_add);
            lpp.add_elem_by_vertex(tabu_add, cpp);
            cpp.add(tabu_remove);
            lpp.del_elem_by_vertex(tabu_remove, cpp);
        }
        else{
            if(lpp.l_size > 0 && cpp.c_size > 0){
                lpp.update_weight();
                int rand_edge = lpp.random_edge();
                int rand_u = cpp.random_elem(), 
                rand_v = edges[rand_edge].v[rand_int(0, 1)];
                cpp.del(rand_u);
                lpp.add_elem_by_vertex(rand_u, cpp); 
                cpp.add(rand_v);
                lpp.del_elem_by_vertex(rand_v, cpp);
            }
        }
        if(cpp.c_size + lpp.l_size  < ub){
            ub = cpp.c_size + lpp.l_size;
            if(lpp.l_size == 0){
                cc = cpp;
            }
            else{
                cc = cpp;
                ll = lpp;
                construct_cp(cc, ll);
            }
            random_remove_vertices(cpp, lpp, 0.6 * cpp.c_size);
        }
        step++;
    }
    printf("%d\n", n - cc.c_size);
    for(i = 1; i <= n; i++){
        if(cc.c_pos[i] == -1){
            printf("%d ", i);
        }
    }
    printf("\n");
}




int main(){
    while(scanf("%d %d", &n, &k) != EOF){
        memset(g1, 0, sizeof(g1));
        memset(g, 0, sizeof(g));
        memset(weight, 0, sizeof(weight));
        ecnt = 0;
        solve();
        lpp.reset();
        cpp.reset();
        for(int i = 1; i <= n; i++){
            vertex[i].clear();
        } 
    }

}
