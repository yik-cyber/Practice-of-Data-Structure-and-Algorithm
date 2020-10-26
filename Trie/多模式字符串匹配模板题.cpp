#include<bits/stdc++.h>
using namespace std;

const int N = 120000 + 10;
int n, m;
struct Node{
    public:
    Node* child[26];
    Node* pnext;
    bool danger;
    Node(){
        memset(child, 0, sizeof(child));
        pnext = nullptr;
        danger = false;
    }
}t[N];

int cnt = 2;
void build_tree(char* s){
    int len = strlen(s);
    Node* p = t + 1;
    for(int i = 0; i < len; i++){
        if(p->child[s[i]-'a'] == nullptr){
            p->child[s[i]-'a'] = t + cnt;
            cnt++;
        }
        p = p->child[s[i]-'a'];
    }
    p->danger = true;
}

void find_next(){
    for(int i = 0; i < 26; i++){
        t[0].child[i] = t + 1;
    }
    t[0].pnext = nullptr;
    t[1].pnext = t;
    queue<Node*> nq;
    nq.push(t + 1);
    while(!nq.empty()){
        Node* father = nq.front();
        nq.pop();

        Node* childs; Node* prev_next;
        for(int i = 0; i < 26; i++){
            childs = father->child[i];
            if(childs){
                prev_next = father->pnext;
                while(prev_next->child[i] == nullptr) prev_next = prev_next->pnext;
                childs->pnext = prev_next->child[i];

                if(childs->pnext->danger) childs->danger = true;
                nq.push(childs);
            }
        }
    }
}

bool match_string(char* tag){
    Node* p = t + 1;
    int len = strlen(tag);
    for(int i = 0; i < len; i++){
        while(p->child[tag[i] - 'a'] == nullptr) p = p->pnext;
        p = p->child[tag[i] - 'a'];
        if(p->danger) return true;
    }
    return false;
}

int main(){
    char subs[130];
    char tags[1010];
    scanf("%d", &n);
    for(int i = 0; i < n; i++){
        scanf("%s", subs);
        build_tree(subs);
    }
    find_next();
    scanf("%d", &m);
    for(int i = 0; i < m; i++){
        scanf("%s", tags);
        if(match_string(tags)){
            printf("YES\n");
        }
        else printf("NO\n");
    }
}
