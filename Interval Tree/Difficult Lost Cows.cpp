#include <bits/stdc++.h>

const int N = 1e5 + 5;
struct Node{
public:
    int l, r, left;
    int mid(){return (l + r) >> 1;}
}t[N << 2];
int n;
int cow[N];

void build(int p, int l, int r){
    t[p].l = l, t[p].r = r;
    t[p].left = r - l + 1;
    if(l == r) return;
    int t_m = t[p].mid();
    build(2*p+1, l, t_m);
    build(2*p+2, t_m+1, r);
}

int query(int p, int place){
    t[p].left--;
    if(t[p].l == t[p].r) return t[p].l;
    if(t[2*p+1].left >= place){
        return query(2*p+1, place);
    }
    else {
        return query(2*p+2, place - t[2*p+1].left);
    }
}

int main(){
    scanf("%d", &n);
    cow[1] = 0;
    build(1, 1, n);
    for(int i = 2; i <= n; i++) scanf("%d", &cow[i]);
    for(int i = n; i >= 1; i--){
        cow[i] = query(1, cow[i]+1);
    }
    for(int i = 1; i <= n; i++){
        printf("%d\n", cow[i]);
    }
}
