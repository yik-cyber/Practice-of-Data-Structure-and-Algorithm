#include<bits/stdc++.h>
using namespace std;

int n;
map<char, int> mp = {{'A', 0}, {'G', 1}, {'C', 2}, {'T', 3}};
struct Node{
    public:
    int child[4];
    int pnext;
    bool danger;
    Node(){
        memset(child, 0, sizeof(child));
        pnext = -1;
        danger = false;
    }
}t[1005];

int cnt = 2;
void build(char* s){
    int p = 1;
    int lens = strlen(s);
    for(int i = 0; i < lens; i++){
        if(t[p].child[mp[s[i]]] == 0){
            t[p].child[mp[s[i]]] = cnt;
            cnt++;
        }
        p = t[p].child[mp[s[i]]];
    }
    t[p].danger = true;
}

void find_next(){
    for(int i = 0; i < 4; i++){
        t[0].child[i] = 1;
    }
    t[0].pnext = -1;
    t[1].pnext = 0;
    queue<int> nq;
    nq.push(1);
    while(!nq.empty()){
        int f = nq.front();
        nq.pop();

        for(int i = 0; i < 4; i++){
            int c = t[f].child[i];
            int fn = t[f].pnext;
            if(c){
                while(t[fn].child[i] == 0) fn = t[fn].pnext;
                t[c].pnext = t[fn].child[i];

                if(t[t[c].pnext].danger) t[c].danger = true;
                nq.push(c);
            }
            else{ //改图
                while(t[fn].child[i] == 0) fn = t[fn].pnext;
                fn = t[fn].child[i];
                t[f].child[i] = fn;
                if(t[fn].danger) t[t[f].child[i]].danger = true;
            }
        }
    }
}

int dp[1005][1005];
char str[1005];
int ans = INT_MAX, len;
void get_dp(){
    for(int i = 1; i <= len; i++){
        for(int j = 1; j < cnt; j++){
            if(t[j].danger || dp[i-1][j] == INT_MAX) continue;
            for(int k = 0; k < 4; k++){
                int sonj = t[j].child[k];
                if(t[sonj].danger) continue;
                dp[i][sonj] = min(dp[i][sonj], dp[i-1][j] + (k != mp[str[i-1]]));
            }
        }
    }
    for(int j = 0; j < cnt; j++){
        ans = min(dp[len][j], ans);
    }
}

void init_dp(){
    for(int i = 0; i < 1005; i++){
        for(int j = 0; j < 1005; j++){
            dp[i][j] = INT_MAX;
        }
    }
}
int main(){
    int cases = 1;
    while(scanf("%d", &n) && n){
        for(int i = 0; i < n; i++){
            scanf("%s", str);
            build(str);
        }
        find_next();
        init_dp();
        scanf("%s", str);
        len = strlen(str);
        dp[0][1] = 0;
        get_dp();
        if(ans == INT_MAX) ans = -1;
        printf("Case %d: %d\n", cases++, ans);
        ans = INT_MAX;
        memset(t, 0, sizeof(t));
        cnt = 2;
    }
}
