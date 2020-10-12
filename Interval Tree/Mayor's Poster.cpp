#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
int n, ans;
int num[N << 1];
map<int, int> mp;
bool vis[N];
struct Node{
public:
    int l, r, pos;
    int mid(){return (l + r) >> 1;}
}t[N << 2];
struct Poster{
public:
    int l, r;
}poster[N];

void build(int p, int l, int r){
    t[p].l = l, t[p].r = r, t[p].pos = 0;
    if(l == r) return;
    int t_m = t[p].mid();
    build(2*p+1, l, t_m);
    build(2*p+2, t_m+1, r);
}

void insert(int p, int l, int r, int i){
    if(t[p].l == l && t[p].r == r){
        t[p].pos = i;
        return;
    }
    int t_m = t[p].mid();
    if(t[p].pos > 0){
        t[2*p+1].pos = t[2*p+2].pos = t[p].pos;
        t[p].pos = 0;
    }
    if(r <= t_m){
        insert(2*p+1, l, r, i);
    }
    else if(l > t_m){
        insert(2*p+2, l, r, i);
    }
    else{
        insert(2*p+1, l, t_m, i);
        insert(2*p+2, t_m+1, r, i);
    }
}

void query(int p){
    if(t[p].pos){
        if(!vis[t[p].pos]){
            ans++;
            vis[t[p].pos] = true;
        }
        return;
    }
    query(2*p+1);
    query(2*p+2);
}

int main(){
    int test;
    scanf("%d", &test);
    while (test--){
        memset(vis, false, sizeof(vis));
        scanf("%d", &n);
        int cnt = 0;
        int i;
        for(i = 1; i <= n; i++){
            scanf("%d %d", &poster[i].l, &poster[i].r);
            num[++cnt] = poster[i].l;
            num[++cnt] = poster[i].r;
        }
        sort(num+1, num+cnt+1);
        int* new_end = unique(num+1, num+cnt+1);
        cnt = new_end - num - 1;
        for(i = 1; i <= cnt; i++){
            mp[num[i]] = i;
        } //离散化
        build(1, 1, cnt);
        for(int i = 1; i <= n; i++){
            insert(1, mp[poster[i].l], mp[poster[i].r], i);
        }
        ans = 0;
        query(1);
        printf("%d\n", ans);
        memset(t, 0, sizeof(t));
        memset(poster, 0, sizeof(poster));
        memset(num, 0, sizeof(num));
    }
}
