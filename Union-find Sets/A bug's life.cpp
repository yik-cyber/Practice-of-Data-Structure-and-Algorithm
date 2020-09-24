#include<bits/stdc++.h>
using namespace std;

int n, m;
bool flag;
int fa[2010], sex[2010];

int get(int x){
	if(x == fa[x]) return x;
	int t = get(fa[x]);
	sex[x] ^= sex[fa[x]];
	fa[x] = t;
	return fa[x];
}
void merge(int x, int y){
	int p = get(x), q = get(y);
	if(p != q){
		fa[q] = p;
		sex[q] = sex[x] ^ sex[y] ^ 1;
        return;
	}
	else{
		if(sex[x] == sex[y]){
			flag = false;
			return;
		}
	}
}

int main(){
	int t, x, y, g = 0;
	scanf("%d", &t);
	while(++g <= t){
		printf("Scenario #%d:\n", g);
		flag = true;
		scanf("%d %d", &n, &m);
		for(int i = 1; i <= n; i++){
			fa[i] = i;
			sex[i] = 0;
		}
		for(int i = 1; i <= m; i++){
		    scanf("%d %d", &x, &y);
		    merge(x, y);		
		}
		if(flag){
			printf("No suspicious bugs found!\n");
		}
		else{
			printf("Suspicious bugs found!\n");
		}
		printf("\n");
	}
}
