#include<bits/stdc++.h>
using namespace std;

const int N = 30000 + 2;
int n;
struct Node{
    public:
    int child[2];
    int pnext;
    bool marker;
    bool danger;
    Node(){
        child[0] = child[1] = -1;
        pnext = -1;
        danger = false;
        marker = false;
    }
}t[N];

int cnt = 2;
void build_tree(char* s){
    int p = 1;
    int len = strlen(s);
    for(int i = 0; i < len; i++){
        if(t[p].child[s[i]-'0'] == -1){
            t[p].child[s[i]-'0'] = cnt;
            cnt++;
        }
        p = t[p].child[s[i]-'0'];
    }
    t[p].danger = true;
}

void find_next(){
    for(int i = 0; i < 2; i++){
        t[0].child[i] = 1;
    }
    t[0].pnext = -1;
    t[1].pnext = 0;
    queue<int> nq;
    nq.push(1);
    while(!nq.empty()){
        int f = nq.front();
        nq.pop();

        for(int i = 0; i < 2; i++){
            int c = t[f].child[i];
            int fn = t[f].pnext;
            if(c){
                while(t[fn].child[i] == -1) fn = t[fn].pnext;
                t[c].pnext = t[fn].child[i];

                if(t[t[c].pnext].danger) t[c].danger = true;
                nq.push(c);
            }
        }
    }
}


bool flag;
void find_ring(int cur){
    if(flag) return;
    if(t[cur].danger) return;
    if(t[cur].marker){
        flag = true;
        return;
    }
    t[cur].marker = true;
    for(int i = 0; i < 2; i++){
        if(t[cur].child[i] >= 0){
            find_ring(t[cur].child[i]);
        }
        else{
            int prev = t[cur].pnext;
            while(t[prev].child[i] == -1) prev = t[prev].pnext;
            find_ring(t[prev].child[i]);
        }
    }
    t[cur].marker = false;
}

int main(){
    scanf("%d", &n);
        char subs[N];
        for(int i = 0; i < n; i++){
            scanf("%s", subs);
            build_tree(subs);
        }
        find_next();
        flag = false;
        find_ring(1);
        if(flag){
            printf("TAK\n");
        }
        else printf("NIE\n");
        memset(t, 0, sizeof(t));
        cnt = 2;
}
