#include<bits/stdc++.h>
using namespace std;

const int N = 300000 + 10;
int c[N];
struct Node{
	public:
		int val;
		int pos;
}t[N];
int n; 
bool operator<(Node a, Node b){
	if(a.val == b.val) return a.pos > b.pos;
	else return a.val < b.val;
}

void change(int x, int v){
	for(; x <= n; x += (x&-x)){
		c[x] = max(c[x], v);
	}
}

int query(int x){
	int sum = 0;
	for(; x > 0; x -= (x&-x)){
		sum = max(sum, c[x]);
	}
	return sum;
}

int main(){
	scanf("%d", &n);
	int x;
	for(int i = 1; i <= n; i++){
		scanf("%d", &x);
		t[i].val = x;
		t[i].pos = i;
	}
	sort(t + 1, t + n + 1);
	int ans = 0, y;
	for(int i = 1; i <= n; i++){
		y = query(t[i].pos) + 1;
		ans = max(ans, y);
		change(t[i].pos, y);
	}
	printf("%d", ans);
}
