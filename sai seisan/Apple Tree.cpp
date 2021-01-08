#include<bits/stdc++.h>
using namespace std;
const int N = 100000 + 10;
vector<vector<int> > fork;
int apple[N], start[N], endd[N];
bool have[N];
int tag, n, m;

void dfs(int x){
	start[x] = ++tag;
	for(int i = 0; i < fork[x].size(); i++){
		int v = fork[x][i];
		dfs(v);
	}
	endd[x] = tag;
}

void change(int x, int c){
	for(; x <= n; x += (x&-x)){
		apple[x] += c;
	}
}

int query(int x){
	int sum = 0;
	for(; x > 0; x -= (x&-x)){
		sum += apple[x];
	}
	return sum;
}

int main(){
	scanf("%d", &n);
	fork.resize(n + 1);
	int f, c;
	for(int i = 1; i < n; i++){
		scanf("%d %d", &f, &c);
		fork[f].push_back(c);
	}
	tag = 0;
	dfs(1);
	for(int i = 1; i <= n; i++){
		change(i, 1);
		have[i] = true;
	}
	scanf("%d", &m);
	char cmd[3];
	int x;
	for(int i = 0; i < m; i++){
		scanf("%s %d", cmd, &x);
		if(cmd[0] == 'Q'){
			printf("%d\n", query(endd[x]) - query(start[x] - 1));
		}
		else{
			if(have[x]){
				change(start[x], -1);
			}
			else change(start[x], 1);
			have[x] = !have[x];
		}
	}
}
