#include<bits/stdc++.h>
using namespace std;

int c[1050][1050], a[1050][1050];
int s;

void change(int x, int y, int val){
	for(; x <= s; x += (x & -x)){
		for(int t = y; t <= s; t += (t & -t)){
			c[x][t] = c[x][t] + val < 0 ? 0 : c[x][t] + val;
		}
	}
}

int query(int x, int y){
	int sum = 0;
	for(; x > 0; x -= (x & -x)){
		for(int t = y; t > 0; t -= (t & -t)){
			sum += c[x][t];
		}
	}
	return sum;
}

int main(){
	int m, cmd;
	scanf("%d %d", &cmd, &s);
	int l, b, r, t, v, ans;
	while(true){
		scanf("%d", &cmd);
		if(cmd == 1){
			scanf("%d %d %d", &l, &b, &v);
			change(l+1, b+1, v);
		}
		else if(cmd == 2){
			scanf("%d %d %d %d", &l, &b, &r, &t);
			l++, b++, r++, t++;
			ans = query(r, t) - query(l - 1, t) - query(r, b - 1) + query(l - 1, b - 1);
			printf("%d\n", ans);
		}
		else break;
	}
	return 0;
}
