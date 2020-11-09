#include<bits/stdc++.h>
using namespace std;

const int N = 810000;
int wa[N], wb[N], wv[N], wss[N];
int sa[N]; int ranks[N];
int height[N];
void suffix_array(char* s, int n, int m){
    int i, j, p;
    int* pm = wa; int* k2sa = wb; int* t;

    for(i = 0; i < m; i++) wss[i] = 0;
    for(i = 0; i < n; i++) wss[pm[i] = s[i]]++;
    for(i = 1; i < m; i++) wss[i] += wss[i-1];
    for(i = n - 1; i >= 0; i--) sa[--wss[pm[i]]] = i;

    for(j = p = 1; p < n; j <<= 1, m = p){
        //k2sa
        for(p = 0, i = n - j; i < n; i++) k2sa[p++] = i;
        for(i = 0; i < n; i++){
            if(sa[i] >= j) k2sa[p++] = sa[i] - j;
        }

        for(i = 0; i < m; i++) wss[i] = 0;
        for(i = 0; i < n; i++) wss[wv[i] = pm[k2sa[i]]]++;
        for(i = 1; i < m; i++) wss[i] += wss[i-1];
        for(i = n - 1; i >= 0; i--) sa[--wss[wv[i]]] = k2sa[i];

        for(t = pm, pm = k2sa, k2sa = t, pm[sa[0]] = 0, p = i = 1; i < n; i++){ //最开始这里写错了一直WA，老眼花了
            int a = sa[i-1], b = sa[i];
            if(k2sa[a] == k2sa[b] && a + j < n && b + j < n && k2sa[a+j] == k2sa[b+j]){
                pm[sa[i]] = p - 1;
            }
            else pm[sa[i]] = p++;
        }
    }
}

void height_array(char* s, int n){
    int i, j, k;
    for(i = 0; i < n; i++) ranks[sa[i]] = i;
    height[0] = 0;
    for(i = k = 0; i < n - 1; height[ranks[i++]] = k){
        for(k? k--: 0, j = sa[ranks[i] - 1]; s[i+k] == s[j+k]; k++);
    }
}

int main(){
    char s1[N];
    char s2[N];
    scanf("%s", s1);
    scanf("%s", s2);
    int len1 = strlen(s1);
    int len2 = strlen(s2);
    s1[len1] = 'z'+1;
    for(int i = 0; i < len2; i++){
        s1[len1 + i + 1] = s2[i];
    }

    s1[len1 + len2 + 1] = '\0';
    
    int len_all = len1 + len2 + 2;
    int m = 128;
    suffix_array(s1, len_all, m);
    height_array(s1, len_all);
    int ans = 0;
    for(int i = 1; i < len_all; i++){
        if((sa[i] < len1 && sa[i-1] > len1) || (sa[i-1] < len1 && sa[i] > len1)){
            ans = max(ans, height[i]);
        }
    }
    printf("%d\n", ans);
}
