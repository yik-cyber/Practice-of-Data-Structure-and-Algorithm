#include<bits/stdc++.h>
using namespace std;

struct CVector{
    public:
    double x, y;
    CVector(){}
    CVector(double _x, double _y):x(_x), y(_y){}
    double operator^(CVector b){
        return x * b.y - b.x * y;
    }
    CVector operator*(double k){
        return CVector(k * x, k * y);
    }
    CVector operator+(CVector b){
        return CVector(x + b.x, y + b.y);
    }
    CVector operator-(CVector b){
        return CVector(x - b.x, y - b.y);
    }
};


struct CLine{
    public:
    CVector x, y;
    CLine(CVector _x, CVector _y):x(_x), y(_y){}
    CLine(){}
};

const double ESP = 1e-6;

bool isZero(double a){
    return fabs(a) < ESP;
}

double area(CVector a, CVector b){
    return (a ^ b) / 2;
}

double length(CVector a){
    return sqrt(a.x * a.x + a.y * a.y);
}
double dis(CVector p, CLine l){
    return fabs(((p - l.x)^(l.y - l.x)) / length(l.y - l.x));
}

void judge(CLine a, CLine b){
    double x = area(a.x - b.x, b.y - b.x);
    double y = area(b.y - b.x, a.y - b.x);
    if(isZero(x + y)){
        if(isZero(dis(a.x, b))){
            printf("LINE\n");
        }
        else printf("NONE\n");
    }
    else{
        CVector interp = a.x + (a.y - a.x)*(x / (x + y));
        printf("POINT %.2lf %.2lf\n", interp.x, interp.y);
    }
}

int main(){
    int n;
    scanf("%d", &n);
    double x1, y1, x2, y2;
    printf("INTERSECTING LINES OUTPUT\n");
    for(int i = 1; i <= n; i++){
        scanf("%lf %lf %lf %lf", &x1, &y1, &x2, &y2);
        CLine l1(CVector(x1, y1), CVector(x2, y2));
            
        scanf("%lf %lf %lf %lf", &x1, &y1, &x2, &y2);
        CLine l2(CVector(x1, y1), CVector(x2, y2));

        judge(l1, l2);
    }
    printf("END OF OUTPUT");
}