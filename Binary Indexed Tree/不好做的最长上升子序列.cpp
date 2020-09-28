#include<bits/stdc++.h>
using namespace std;

int num;
pair<int, int> n[300010];
int c[300010];

void update(int x, int val){
    for(; x <= num; x += (x & -x)){
        c[x] = max(c[x], val);
    }
}

int query(int x){
    int maxl = 0;
    for(; x > 0; x -= (x & -x)){
        maxl = max(maxl, c[x]);
    }
    return maxl;
}

bool cmp(pair<int, int> a, pair<int, int> b){
    if(a.first == b.first) return a.second > b.second;
    return a.first < b.first;
}
int main(){
    scanf("%d", &num);
    for(int i = 1; i <= num; i++){
        scanf("%d", &n[i].first);
        n[i].second = i;
    }
    sort(n+1, n+num+1, cmp);
    int tmp_lis;
    for(int i = 1; i <= num; i++){
        tmp_lis = query(n[i].second) + 1;
        update(n[i].second, tmp_lis);
    }
    printf("%d", query(num));
    return 0;
}
