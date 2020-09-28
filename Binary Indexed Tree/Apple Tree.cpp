#include<bits/stdc++.h>
#include<vector>
using namespace std;

int n,m,key;
int start[100010], over[100010], c[100010];
bool have_apple[100010];
vector<int> edge[100010];

void dfs(int x){
    start[x] = key;
    for(int i = 0; i < edge[x].size(); i++){
        key++;
        dfs(edge[x][i]);
    }
    over[x] = key;
}

void change(int x, int val){
    for(; x <= n; x += (x & (-x))){
        c[x] += val;
    }
}

int query(int x){
    int sum = 0;
    for(; x > 0; x -= (x & (-x))){
        sum += c[x];
    }
    return sum;
}

int main(){
    scanf("%d", &n);
    int r, b;
    for(int i = 1; i < n; i++){
        scanf("%d %d", &r, &b);
        edge[r].push_back(b);
    }
    key = 1;
    dfs(1);
    for(int i = 1; i <= n; i++){
        change(i, 1);
        have_apple[i] = true;
    }
    int t, change_num;
    char cmd;
    scanf("%d", &m);
    for(int i = 1; i <= m; i++){
        getchar();
        scanf("%c", &cmd);
        scanf("%d", &t);
        if(cmd == 'C'){
            change_num = have_apple[t]? -1:1;
            change(start[t], change_num);
            //change(over[t], change_num); only change one start point, so the answer do not need to divide 2
            have_apple[t] = !have_apple[t];
        }
        else{
            int ans = query(over[t]) - query(start[t] - 1);
            printf("%d\n", ans);
        }
    }
    return 0;

}
