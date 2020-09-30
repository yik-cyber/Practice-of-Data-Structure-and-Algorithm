#include<bits/stdc++.h>
using namespace std;

const int N = 100001;
int n;
int c[100010], ans[100010];
struct Cow{
public:
    int pos, s, e;
    bool operator<(Cow b){
        if(e == b.e) return s < b.s;
        else return e > b.e;
    }
}cow[100010];


void update(int x, int val){
    for(; x <= N; x += (x & -x)){
        c[x] += val;
    }
}

int query(int x){
    int sum = 0;
    for(; x > 0; x -= (x & -x)){
        sum += c[x];
    }
    return sum;
}

int main(){
    while (scanf("%d", &n) && n){
        for(int i = 1; i <= n; i++){
            scanf("%d %d", &cow[i].s, &cow[i].e);
            cow[i].s++; cow[i].e++;
            cow[i].pos = i;
        }
        sort(cow+1, cow+n+1);
        for(int i = 1; i <= n; i++){
            if(cow[i].e == cow[i-1].e && cow[i].s == cow[i-1].s){
                ans[cow[i].pos] = ans[cow[i-1].pos];
            }
            else ans[cow[i].pos] = query(cow[i].s);
            update(cow[i].s, 1);
        }
        for(int i = 1; i <= n; i++){
            printf("%d ", ans[i]);
        }
        printf("\n");
        memset(c, 0, sizeof(c));
        memset(ans, 0, sizeof(ans));
    }
}
