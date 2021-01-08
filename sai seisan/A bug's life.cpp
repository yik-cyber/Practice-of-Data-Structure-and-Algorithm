#include<bits/stdc++.h>
using namespace std;
const int N = 2000 + 10;
int fa[N], rel[N];

int get_fa(int x){
	if(x == fa[x]) return x;
	int t = get_fa(fa[x]);
	rel[x] = rel[x] ^ rel[fa[x]];
	return fa[x] = t;
} 

int merge(int x, int y){
	int p = get_fa(x), q = get_fa(y);
	if(p == q){
		return rel[x]^rel[y];
	}
	else{
		fa[q] = p;
		rel[q] = rel[x] ^ rel[y] ^ 1;
		return -1;
	}
}
int t, n, m;
int main(){
	scanf("%d", &t);
	for(int i = 1; i <= t; i++){
		scanf("%d %d", &n, &m);
		for(int j = 1; j <= n; j++){
			fa[j] = j;
			rel[j] = 0;
		}
		bool flag = true;
		int x, y;
		for(int j = 0; j < m; j++){
			scanf("%d %d", &x, &y);
			if(!flag) continue;
			int v = merge(x, y);
			if(v == 0) flag = false;
		}
		printf("Scenario #%d:\n\n", i);
		if(flag) printf("No suspicious bugs found!\n");
		else printf("Suspicious bugs found!\n");
	}
}
