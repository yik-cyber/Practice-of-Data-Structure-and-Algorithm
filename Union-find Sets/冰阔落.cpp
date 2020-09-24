#include<bits/stdc++.h>
#include<vector>
using namespace std;

int n, m, cnt;
int fa[50010];

int get(int x){
	return x == fa[x]? x:fa[x] = get(fa[x]);
}
bool merge(int x, int y){
	int p = get(x), q = get(y);
	if(p == q){
		return true;
	}
	fa[q] = p;
	cnt--;
	return false;
}

int main(){
	while (scanf("%d %d", &n, &m) != EOF){
		cnt = n;
		memset(fa, 0, sizeof(fa));
		for(int i = 1; i <= n; i++){
		fa[i] = i;
	    }
	    int c1, c2;
	    for(int i = 1; i <= m; i++){
		    scanf("%d %d", &c1, &c2);
		    if(merge(c1, c2)) printf("Yes\n");
		    else printf("No\n");
	    }
	    printf("%d\n", cnt);
	    for(int i = 1; i <= n; i++){
		    if(fa[i] == i){
			    printf("%d ", i);
		    }
	    }
	    printf("\n");
	}
}
