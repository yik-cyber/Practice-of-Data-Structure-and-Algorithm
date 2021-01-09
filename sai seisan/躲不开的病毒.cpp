#include<bits/stdc++.h>
using namespace std;
const int N = 30000;
struct Node{
    public:
    int ch[2];
    int pnext;
    bool danger = false;
    bool marker;
}t[N];

int cnt = 1;
void build(char* s, int len){
    int p = 1;
    for(int i = 0; i < len; i++){
        int c = s[i] - '0';
        if(t[p].ch[c] == 0){
            t[p].ch[c] = ++cnt;
        }
        p = t[p].ch[c];
    }
    t[p].danger = true;
}


void find_pnext(){
    for(int i = 0; i < 2; i++){
        t[0].ch[i] = 1;
    }
    t[1].pnext = 0;
    queue<int> nq;
    nq.push(1);
    while(!nq.empty()){
        int f = nq.front();
        nq.pop();

        for(int i = 0; i < 2; i++){
            int c = t[f].ch[i];
            int fn = t[f].pnext;
            while(t[fn].ch[i] == 0) fn = t[fn].pnext;
            if(c){
                t[c].pnext = t[fn].ch[i];

                if(t[t[c].pnext].danger) t[c].danger = true;
                nq.push(c);
            }
            else{
                t[f].ch[i] = t[fn].ch[i];
            } 
        }
    }
}
bool flag = false;
void dfs(int cur){
    if(flag) return;
    if(t[cur].danger) return;
    if(t[cur].marker){
        flag = true;
        return;
    }
    t[cur].marker = true;
    for(int i = 0; i < 2; i++){
        int c = t[cur].ch[i];
        dfs(c);
    }
    t[cur].marker = false;
}
int n, m;
int main(){
    char str[N];
    scanf("%d", &n);
    for(int i = 0; i < n; i++){
        scanf("%s", str);
        build(str, strlen(str));
    }
    find_pnext();
    dfs(1);
    if(flag) printf("TAK\n");
    else printf("NIE\n");
    
}
