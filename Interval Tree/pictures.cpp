#include<bits/stdc++.h>
using namespace std;

const int N = 1e4 + 10;
int n;
struct Node{
    public:
    int l, r, segs, len, covers;
    bool lcovered, rcovered;
}t[N << 2];
struct CLine{
    public:
    int x, y1, y2;
    int left;
    bool operator<(CLine b){
        if(x == b.x) return left > b.left; //一定要判断，呜呜呜呜呜呜呜呜
        return x < b.x;
    }
}line[N];
int ycord[N];
map<int, int> mp;

void build(int p, int l, int r){
    t[p].l = l, t[p].r = r;
    t[p].segs = 0, t[p].len = 0;
    t[p].covers = 0;
    t[p].lcovered = t[p].rcovered = false;
    if(l == r) return;
    int m = (l + r) >> 1;
    build(2*p+1, l, m);
    build(2*p+2, m+1, r);
}

void update(int p){
    if(t[p].covers){
        t[p].len = ycord[t[p].r+1] - ycord[t[p].l];
        t[p].lcovered = t[p].rcovered = true;
        t[p].segs = 1;
    }
    else if(t[p].l == t[p].r){
        t[p].len = t[p].segs = 0;
        t[p].lcovered = t[p].rcovered = false;
    }
    else{ //没有被完全覆盖
        t[p].len = t[2*p+1].len + t[2*p+2].len;
        t[p].lcovered = t[2*p+1].lcovered, t[p].rcovered = t[2*p+2].rcovered;
        t[p].segs = t[2*p+1].segs + t[2*p+2].segs - (t[2*p+1].rcovered && t[2*p+2].lcovered);
    }
}
void insert(int p, int l, int r, int lft){
    if(t[p].l == l && t[p].r == r){
        t[p].covers += lft;
        update(p);
        return;
    }
    int t_m = (t[p].l + t[p].r) >> 1;
    if(r <= t_m){
        insert(2*p+1, l, r, lft);
    }
    else if(l > t_m){
        insert(2*p+2, l, r, lft);
    }
    else{
        insert(2*p+1, l, t_m, lft);
        insert(2*p+2, t_m+1, r, lft);
    }
    update(p);
}


int main(){
    scanf("%d", &n);
    int x1, x2, y1, y2;
    int cnt = 0, yc = 1;
    for(int i = 1; i <= n; i++){
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
        cnt++;
        line[cnt].x = x1, line[cnt].y1 = y1, line[cnt].y2 = y2;
        line[cnt].left = 1;
        cnt++;
        line[cnt].x = x2, line[cnt].y1 = y1, line[cnt].y2 = y2;
        line[cnt].left = -1;
        ycord[yc++] = y1, ycord[yc++] = y2;
    }
    sort(ycord+1, ycord+yc);
    int* yt = unique(ycord+1, ycord+yc); // the number of horizonal lines
    yc = yt - ycord - 1;
    for(int i = 1; i <= yc; i++){
        mp[ycord[i]] = i; // 纵坐标编号
    }
    build(1, 1, yc - 1);
    int tot_len = 0;
    int last = 0;
    sort(line+1, line+cnt+1); //sort the lines
    for(int i = 1; i <= cnt; i++){
        int l = mp[line[i].y1], r = mp[line[i].y2] - 1;
        insert(1, l, r, line[i].left);
        tot_len += abs(t[1].len - last);
        tot_len += 2 * t[1].segs * (line[i+1].x - line[i].x);
        last = t[1].len;
    }
    printf("%d\n", tot_len);
}
