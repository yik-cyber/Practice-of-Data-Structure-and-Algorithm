#include <bits/stdc++.h>
using namespace std;

const int N = 1e5+5;
int n[N];
int sorted[N];
vector<int> t[4*N];

int num, m;

void build(int p, int l, int r){
    if(l == r){
        t[p].push_back(n[l]);
        return;
    }
    int t_m = (l+r)>>1;
    int lc = 2*p+1, rc = 2*p+2;
    build(lc, l, t_m);
    build(rc, t_m+1, r);

    int i = 0, j = 0;
    while(i < t[lc].size() && j < t[rc].size()){
        while(i < t[lc].size() && t[lc][i] <= t[rc][j]){
            t[p].push_back(t[lc][i++]);
        }
        while(j < t[rc].size() && t[rc][j] <= t[lc][i]){
            t[p].push_back(t[rc][j++]);
        }
    }
    while(i < t[lc].size()) t[p].push_back(t[lc][i++]);
    while(j < t[rc].size()) t[p].push_back(t[rc][j++]);
}


int query(int p, int l, int r, int x, int pl, int pr){ //有多少比x小的数
    if(pl >= l && pr <= r){
         return upper_bound(t[p].begin(), t[p].end(), x) - t[p].begin();
    }
    int pm = (pl+pr) >> 1;
    if(r <= pm){
        return query(2*p+1, l, r, x, pl, pm);
    }
    else if(l > pm){
        return query(2*p+2, l, r, x, pm+1, pr);
    }
    else{
        return query(2*p+1, l, pm, x, pl, pm) + query(2*p+2, pm+1, r, x, pm+1, pr);
    }
}

int search(int li, int ri, int ki){
    int l = 1, r = num, mid, tmp;
    while(l < r){
        mid = (l + r) >> 1;
        tmp = query(1, li, ri, sorted[mid], 1, num);
        if(tmp >= ki) r = mid;
        else l = mid + 1;
    }
    return sorted[l];
}

int main(){
    scanf("%d %d", &num, &m);
    for(int i = 1; i <= num; i++){
        scanf("%d", &n[i]);
        sorted[i] = n[i];
    }
    sort(sorted+1, sorted+num+1);
    build(1, 1, num);
    int i, j, k;
    for(int q = 1; q <= m; q++){
        scanf("%d %d %d", &i, &j, &k);
        printf("%d\n", search(i, j, k));
    }
}
