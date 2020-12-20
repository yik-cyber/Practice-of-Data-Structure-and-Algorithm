#include<bits/stdc++.h>
using namespace std;

const int N = 16 * 3;
struct CPoint{
    public:
    char ch;
    double x, y;
    CPoint(double _x, double _y):x(_x), y(_y){}
    CPoint(){}
    CPoint operator-(CPoint b){
        return CPoint(x - b.x, y - b.y);
    }
    double operator^(CPoint b){
        return x * b.y - b.x * y;
    }
}p[N];

const double ESP = 1e-6;

bool isZero(double x){
    return fabs(x) < ESP;
}

double  area(CPoint a, CPoint b, CPoint c){
    return fabs(((b - a) ^ (c - a))) / 2.0;
}

void solve(int n){
    double x, y;
    for(int i = 1; i <= n; i++){
        getchar();
        scanf("%c %lf %lf", &p[i].ch, &p[i].x, &p[i].y);
    }
    double maxa = -1;
    char maxch[4];
    maxch[3] = '\0';
    for(int i = 1; i < n - 1; i++){
        for(int j = i + 1; j < n; j++){
            for(int k = j + 1; k <= n; k++){
                bool flag = true;
                double s = area(p[i], p[j], p[k]);
                if(s < maxa) continue;
                for(int l = 1; l <= n; l++){
                    if(l == i || l == j || l == k) continue;
                    double s1 = area(p[i], p[j], p[l]),
                           s2 = area(p[j], p[k], p[l]),
                           s3 = area(p[k], p[i], p[l]);
		            double sum = (s1 + s2 + s3);
                    if(isZero(s - sum)){
                        flag = false;
                        break;
                    }
                }
                if(flag){
                    if(s > maxa){
                        maxa = s;
                        maxch[0] = p[i].ch;
                        maxch[1] = p[j].ch;
                        maxch[2] = p[k].ch;
                    }
                }
            }
        }
    }
    printf("%s\n", maxch);
}


int main(){
    int m;
    while (scanf("%d", &m) && m != 0){
        solve(m);
    }
}
