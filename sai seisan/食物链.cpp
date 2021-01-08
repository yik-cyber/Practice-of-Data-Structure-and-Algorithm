#include<bits/stdc++.h>
using namespace std;
const int N = 50000 + 10;
int fa[N], rel[N];

int get_fa(int x){
	if(x == fa[x]) return x;
	int t = get_fa(fa[x]);
	rel[x] = (rel[x] + rel[fa[x]]) % 3;
	return fa[x] = t;
}

int merge(int x, int y, int v){
	int p = get_fa(x), q = get_fa(y);
	if(p == q){
		return (rel[x] - rel[y] + 3) % 3;
	}
	else{
		fa[p] = q;
		rel[p] = (-rel[x] + rel[y] + 3 + v) % 3;
		return -1;
	}
}
int n, m;
int main(){
	scanf("%d %d", &n, &m);
	for(int i = 1; i <= n; i++){
		fa[i] = i;
		rel[i] = 0;
	}
	int ans = 0;
	int c, x, y;
	for(int i = 0; i < m; i++){
		scanf("%d %d %d", &c, &x, &y);
		if(x > n || y > n){
			ans++;
			continue;
		}
		if(c == 1){
			int t = merge(x, y, 0);
			if(t >= 0 && t != 0){
				ans++;
				continue;
			}
		}
		else{
			int t = merge(x, y, 1);
			if(t >= 0 && t !=  1){
				ans++;
				continue;
			}
		}
	}
	printf("%d", ans);
}
