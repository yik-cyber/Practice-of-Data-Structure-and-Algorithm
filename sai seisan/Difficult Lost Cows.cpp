#include<bits/stdc++.h>
using namespace std;
const int N = 100000 + 10;
int t[N << 2];

void build(int p, int l, int r){
	if(l == r){
		t[p] = 1;
		return;
	}
	int m = (l + r) >> 1;
	build(2*p+1, l ,m);
	build(2*p+2, m+1, r);
	t[p] = r - l + 1;
}

void delete_node(int p, int l, int r, int v){
	if(l == r){
		t[p] -= 1;
		return;
	}
	int m = (l + r) >> 1;
	if(v <= m){
		delete_node(2*p+1, l, m, v);
	}
	else delete_node(2*p+2, m+1, r, v);
	t[p] -= 1;
}

int query(int p, int l, int r, int v){
	if(l == r){
		return l;
	}
	int m = (l + r) >> 1;
	int lp = 2 * p + 1, rp = 2 * p + 2;
	if(v <= t[lp]){
		return query(lp, l, m, v);
	}
	else{
		return query(rp, m+1, r, v - t[lp]);
	}
}
int cow[N];
int n;
int main(){
	scanf("%d", &n);
	for(int i = 2; i <= n; i++){
		scanf("%d", &cow[i]);
	}
	cow[1] = 0;
	build(1, 1, n);
	for(int i = n; i >= 1; i--){
		int ans = query(1, 1, n, cow[i] + 1);
		delete_node(1, 1, n, ans);
		cow[i] = ans;
	}
	for(int i = 1; i <= n; i++){
		printf("%d\n", cow[i]);
	}
}
