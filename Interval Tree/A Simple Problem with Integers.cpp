#include<bits/stdc++.h>
using namespace std;

const int N = 100000;
struct Node{
public:
    int l, r;
    long long sum, inc;
    int mid(){
        return (l+r) / 2;
    }
}t[4 * N];
int n, m;

void build(int p, int l, int r){
    t[p].l = l, t[p].r = r;
    t[p].sum = t[p].inc = 0;
    if(l == r){
        return;
    }
    int mid = t[p].mid();
    build(2*p+1, l, mid);
    build(2*p+2, mid+1, r);
}

void insert(int p, int i, int val){
    if(t[p].l == i && t[p].r == i){
        t[p].sum = val;
        return;
    }
    t[p].sum += val;
    int t_mid = t[p].mid();
    if(i <= t_mid){
        insert(2*p+1, i, val);
    }
    else insert(2*p+2, i, val);
}

void add(int p, int l, int r, long long val){
    if(t[p].l == l && t[p].r == r){
        t[p].inc += val;
        return;
    }
    t[p].sum += val*(r - l + 1);
    int t_mid = t[p].mid();
    if(r <= t_mid){
        add(2*p+1, l, r, val);
    }
    else if(l > t_mid){
        add(2*p+2, l, r, val);
    }
    else{
        add(2*p+1, l, t_mid, val);
        add(2*p+2, t_mid+1, r, val);
    }
}

long long query(int p, int l, int r){
    if(t[p].l == l && t[p].r == r){
        return t[p].sum + (r - l + 1)*t[p].inc;
    }
    t[p].sum += (t[p].r - t[p].l + 1) * t[p].inc;
    t[2*p+1].inc += t[p].inc;
    t[2*p+2].inc += t[p].inc;
    t[p].inc = 0;

    int t_mid = t[p].mid();
    if(r <= t_mid){
        return query(2*p+1, l, r);
    }
    else if(l > t_mid){
        return query(2*p+2, l, r);
    }
    else{
        return query(2*p+1, l, t_mid) + query(2*p+2, t_mid+1, r);
    }
}

int main(){
    scanf("%d %d", &n, &m);
    build(1, 1, n);
    int j;
    for(int i = 1; i <= n; i++){
        scanf("%d", &j);
        insert(1, i, j);
    }
    char cmd[3];
    int a, b, c;
    for(int i = 1; i <= m; i++){
        scanf("%s", cmd);
        if(cmd[0] == 'C'){
            scanf("%d %d %d", &a, &b, &c);
            add(1, a, b, c);
        }
        else{
            scanf("%d %d", &a, &b);
            printf("%lld\n", query(1, a, b));
        }
    }
}
