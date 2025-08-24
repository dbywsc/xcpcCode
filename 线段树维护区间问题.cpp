#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
int a[N];
struct Node{
    int lv, rv; // 左右端点
    int pre;        //前缀
    int suf;        //后缀
    int max;        //区间最大值
    int len;    // 总长度
}w[N * 4];
void pushup(int u) {
    Node &l = w[u * 2], &r = w[u * 2 + 1];
    //update left right
    w[u].lv = l.lv;
    w[u].rv = r.rv;
    //clac max len
    if(l.rv != r.lv) w[u].max = max({l.max, r.max, l.suf + r.pre});
    else w[u].max = max(l.max, r.max);
    //update pre
    if(l.pre == l.len && l.rv != r.lv) {
        w[u].pre = l.len + r.pre;
    } else {
        w[u].pre = l.pre;
    }
    //update suf
    if(r.suf == r.len && l.rv != r.lv) w[u].suf= r.len + l.suf;
    else w[u].suf = r.suf;

    //total len
    w[u].len = l.len + r.len;
}
void build(int u, int L, int R) {
    if(L == R) {
        w[u].lv = w[u].rv = 0;
        w[u].pre = w[u].suf = w[u].max = w[u].len = 1;
        return;
    }
    int M = (L + R) / 2;
    build(u * 2, L, M); build(u * 2 + 1, M + 1, R);
    pushup(u);
}
void update(int u, int L, int R, int p) {
    if(L == R) {
        w[u].lv ^= 1;
        w[u].rv ^= 1;
        return;
    }
    else {
        int M = (L + R) / 2;
        if(M >= p) update(u * 2, L, M, p);
        else update(u * 2 + 1, M + 1, R, p);
        pushup(u);
    }
}
int main(void) {
    int n, m; cin >> n >> m;
    build(1, 1, n);
    while(m--) {
        int x; cin >> x;
        update(1, 1, n, x);
        cout << w[1].max << endl;
    }
    return 0; 
}
