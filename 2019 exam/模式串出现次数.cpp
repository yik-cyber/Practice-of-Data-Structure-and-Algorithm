#include<bits/stdc++.h>
using namespace std;
const int N = 55;
struct Node{
	public:
		int ch[2];
		int danger;
		int pnext;
}t[N*1000];
int cnt = 1;

void build(char* s){
	int c, p = 1, len = strlen(s);
	for(int i = 0; i < len; i++){
		c = s[i] - '0';
		if(t[p].ch[c] == 0){
			t[p].ch[c] = ++cnt;
		}
		p = t[p].ch[c];
	}
	t[p].danger++;
} 

void find_pnext(){
	for(int i = 0; i < 2; i++){
		t[0].ch[i] = 1;
	}
	t[1].pnext = 0;
	queue<int> nq;
	nq.push(1);
	
	while(!nq.empty()){
		int f = nq.front();
		nq.pop();
		
		for(int i = 0; i < 2; i++){
			int c = t[f].ch[i];
			if(c){
				int fp = t[f].pnext;
				while(t[fp].ch[i] == 0) fp = t[fp].pnext;
				t[c].pnext = t[fp].ch[i];
				
				//if(t[t[c].pnext].danger) t[c].danger = t[t[c].pnext].danger;
				nq.push(c);
			}
		}
	}
	return;
}

int match_str(char* s){
	int len = strlen(s), p = 1, sum = 0, c;
	int i = 0;
	for(int i = 0; i < len; i++){
		c = s[i]-'0';
		while(t[p].ch[c] == 0) p = t[p].pnext;
		p = t[p].ch[c];
		int tmp=p;
		while(tmp!= 0){
			if(t[tmp].danger > 0) sum += t[tmp].danger;
			tmp = t[tmp].pnext;
		}
    }
	return sum;
}
int n, m;
char str[1010];
int main(){
	while(scanf("%d", &n) == 1){
		for(int i = 0 ; i < n; i++){
			scanf("%s", str);
			build(str);
		}
		find_pnext(); 
		scanf("%d", &m);
		for(int i = 0; i < m; i++){
			scanf("%s", str);
			int ans = match_str(str);
			printf("%d\n", ans);
		}
		memset(t, 0, sizeof(t));
		cnt = 1;
	}
}
