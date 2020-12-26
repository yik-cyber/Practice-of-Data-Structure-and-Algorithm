#include<bits/stdc++.h>
using namespace std;

const int N = 1000 + 10;
int n;
struct Point{
    public:
    double x, y;
    double distance(Point& b){
        return hypot(x - b.x, y - b.y);
    }
}p[N];

Point origion;

int is_turn_left(Point& p0, Point& p1, Point& p2){
    //turn left return > 0, right return < 0
    return (p1.x - p0.x)*(p2.y - p0.y) - (p1.y - p0.y)*(p2.x - p0.x); 
}

bool cmp(Point& p1, Point& p2){
    int tf = is_turn_left(p[0], p1, p2);
    if(tf > 0) return true; //p1 < p2
    else if(tf == 0) return (p[0].distance(p1) < p[0].distance(p2));
    else return false; //p2 < p1
}

bool judge(Point& p1, Point& p2){
    for(int i = 0; i < n; i++){
        Point& p3 = p[i];
        if((p3.x == p1.x && p3.y == p1.y) || (p3.x == p2.x && p3.y == p2.y)){
            continue;
        }
        if(((p3.x - p1.x) * (p2.y - p1.y) == (p2.x - p1.x) * (p3.y - p1.y))
           &&(min(p2.x, p1.x) <= p3.x && p3.x <= max(p2.x, p1.x))
           &&(min(p2.y, p1.y) <= p3.y && p3.y <= max(p2.y, p1.y))){
               return false;
           }
    }
    return true;
}


int main(){
    int t, i, j, k;
    double x, y;
    scanf("%d", &t);
    while(t--){
        bool flag = true;
        scanf("%d", &n);
        for(i = 0; i < n; i++){
            scanf("%lf %lf", &p[i].x, &p[i].y);
            if(i == 0){
                k = 0;
                origion = p[0];
                continue;
            }
            if(p[i].y < origion.y || (p[i].y == origion.y && p[i].x < origion.x)){
                origion = p[i];
                k = i;
            }
        }
        if(n < 6){
            printf("NO\n");
            continue;
        }
        p[k] = p[0];
        p[0] = origion;
        sort(p + 1, p + n, cmp);
        Point st[N];
        st[0] = p[0];
        st[1] = p[1];
        int top = 1;
        for(i = 2; i < n; i++){
            st[++top] = p[i];
            while(top > 1 && is_turn_left(st[top - 2], st[top-1], st[top]) <= 0)
                st[top-1] = st[top], --top;
        }
        if(top < 2){
            printf("NO\n");
            continue;
        }
        st[++top] = st[0];
        for(i = 1; i <= top; i++){
            if(judge(st[i-1], st[i])){
                flag = false;
                break;
            }
        }
        if(flag) printf("YES\n");
        else printf("NO\n");
    }
}
