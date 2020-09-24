#include<bits/stdc++.h>
using namespace std;

int n, m;
int fa[50010], rel[50010];


int get(int x){
	if(x == fa[x]){
		return x;
	}
	int t = get(fa[x]);
	rel[x] = (rel[x] + rel[fa[x]]) % 3;
	fa[x] = t;
	return fa[x];
}

void merge(int x, int y, int r){
	int p = get(x), q = get(y);
	fa[p] = q;
	rel[p] = (rel[y] - rel[x] + 3 + r) % 3;
	return;
}

int main(){
	scanf("%d %d", &n, &m);
	for(int i = 1; i <= n; i++){
		fa[i] = i;
	}
	int cnt = 0;
	int x, y, c;
	for(int i = 1; i <= m; i++){
		scanf("%d %d %d", &c, &x, &y);
		if(x > n || y > n) cnt++;
		else if(c == 2 && x == y) cnt++;
		else{
			int p = get(x), q = get(y);
			if(p == q){
                if(c == 1){
                    if(rel[x] != rel[y]) cnt++;
                }
                else if(c == 2){
                    if(rel[x] == 0 && rel[y] != 2) cnt++;
                    else if(rel[x] == 1 && rel[y] != 0) cnt++;
                    else if(rel[x] == 2 && rel[y] != 1) cnt++;
                }
			}
			else merge(x, y, c-1);

		}
	}
	printf("%d", cnt);
}
