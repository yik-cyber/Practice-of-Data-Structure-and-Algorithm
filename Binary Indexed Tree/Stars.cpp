#include<bits/stdc++.h>
#include<map>
using namespace std;

const int N = 32001;
int n;
int c[32010], record[15010];

void update(int x){
    for(; x <= N; x += (x & -x)) c[x]++;
}

int query(int x){
    int sum = 0;
    for(; x > 0; x -= (x & -x)) sum += c[x];
    return sum;
}

int main(){
    scanf("%d", &n);
    int x, y;
    for(int i = 1; i <= n; i++){
        scanf("%d %d", &x, &y);
        x++;
        record[query(x)]++;
        update(x);
    }
    for(int i = 0; i < n; i++){
        printf("%d\n", record[i]);
    }
    return 0;
}
