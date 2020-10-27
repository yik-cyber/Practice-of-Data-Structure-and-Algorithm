#include<cstdio>
#include<algorithm>
#include<queue>
#include<cstring>
using namespace std;

const int N = 5100000 + 10;
int test, n;
struct Node{
    public:
    int child[26];
    int pnext;
    //bool danger;
    int count;
    Node(){
        memset(child, 0, sizeof(child));
        pnext = 0;
        //danger = false;
        count = 0;
    }
}t[250 * 1000 + 10];

int cnt = 2;
void build(char* s){
    int p = 1;
    int len = strlen(s);
    for(int i = 0; i < len; i++){
        if(t[p].child[s[i] - 'A'] == 0){
            t[p].child[s[i] - 'A'] = cnt;
            cnt++;
        }
        p = t[p].child[s[i] - 'A'];
    }
    t[p].count++;
}

void find_next(){
    for(int i = 0; i < 26; i++){
        t[0].child[i] = 1;
    }
    t[0].pnext = -1;
    t[1].pnext = 0;
    queue<int> nq;
    nq.push(1);
    while(!nq.empty()){
        int f = nq.front();
        nq.pop();

        for(int i = 0; i < 26; i++){
            int c = t[f].child[i];
            int fn = t[f].pnext;
            if(c){
                while(t[fn].child[i] == 0) fn = t[fn].pnext;
                t[c].pnext = t[fn].child[i];

                //if(t[t[c].pnext].danger) t[c].danger = true;
                nq.push(c);
            }
        }
    }
}

int match_num(char* s){
    int ans = 0;
    int p = 1;
    int len = strlen(s);
    for(int i = 0; i < len; i++){
        while(t[p].child[s[i] - 'A'] == 0 && p != 1) p = t[p].pnext;
        
        if(t[p].child[s[i] - 'A'])
            p = t[p].child[s[i] - 'A'];
        
        int tmp = p;
        while (tmp && t[tmp].count != -1) { // the matched substring 
            ans += t[tmp].count;
            t[tmp].count = -1;
            tmp = t[tmp].pnext;       
        }
    }
    return ans;
}

int main(){
    scanf("%d", &test);
    char tag[N];
    while (test--){
        scanf("%d", &n);
        for(int i = 0; i < n; i++){
            scanf("%s", tag);
            build(tag);
        }
        memset(tag, 0, sizeof(tag));
        find_next();
        getchar();
        char ch; int i = 0; int lens;
        while(scanf("%c", &ch)){
            if(ch == '\n') break;
            else if(ch == '['){
                scanf("%d", &lens);
                scanf("%c", &ch);
                for(int j = 0; j < lens; j++){
                    tag[i++] = ch;
                }
                scanf("%c", &ch);
            }
            else{
                tag[i++] = ch;
            }
        }
        tag[i] = '\0';
        int out = match_num(tag);
        reverse(tag, tag + i);
        out += match_num(tag);
        printf("%d\n", out);
        cnt = 2;
        memset(t, 0, sizeof(t));
    }
    
}
