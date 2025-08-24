#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
const int N = 1e6 + 10;
i64 a[N], w[N * 4];
i64 lzy[N * 4];
void makeTag(int u, int len, i64 x) {
    lzy[u] += x;
    w[u] += len * x;
}
void pushup(const int u) {
    w[u] = w[u * 2] + w[u * 2 + 1];
}
void pushdown(int u, int L, int R) {
    int M = (L + R) / 2;
    makeTag(u * 2, M - L + 1, lzy[u]);
    makeTag(u * 2 + 1, R - M, lzy[u]);
    lzy[u] = 0;
}
void build(const int u, int L, int R) {
    if(L == R) {
        w[u] = a[L];
        return;
    }
    int M = (L + R) / 2;
    build(u * 2, L, M); build(u * 2 + 1, M + 1, R);
    pushup(u);
}
i64 query1(int u, int L, int R, int p) {
    if(L == R) return w[u];
    int M = (L + R) / 2;
    if(M >= p) return query1(u * 2, L, M, p);
    else return query1(u * 2 + 1, M + 1, R, p);
}
void update1(int u, int L, int R, int p, i64 x) {
    if(L == R) w[u] = x; 
    else {
        int M = (L + R) / 2;
        if(M >= p) update1(u * 2, L, M, p, x);
        else update1(u * 2 + 1, M + 1, R, p, x);
        pushup(u);
    }
}
bool inRange(int L, int R, int l, int r) {
    return (l <= L) && (R <= r);
}
bool outOfRange(int L, int R, int l, int r) {
    return (L > r) || (R < l);
}
i64 query2(int u, int L, int R, int l, int r) {
    if(inRange(L, R, l, r)) return w[u];
    else if(!outOfRange(L, R, l, r)) {
        int M = (L + R) / 2;
        pushdown(u, L, R);
        return query2(u * 2, L, M, l, r) + query2(u * 2 + 1, M + 1, R, l, r);
    }
    else return 0;
}
void update2(int u, int L, int R, int l, int r, i64 x) {
    if(inRange(L, R, l, r)) {
        makeTag(u, R - L + 1, x);
    } else if(!outOfRange(L, R, l, r)) {
        int M = (L + R) / 2;
        pushdown(u, L, R);
        update2(u * 2, L, M, l, r, x);
        update2(u * 2 + 1, M + 1, R, l , r, x);
        pushup(u);
    }
}
int main(void) {
    int n, m; cin >> n >> m;
    for(int i = 1; i <= n;i ++) cin >> a[i];
    build(1, 1, n);
    for(int t = 1; t <= m; t++) {
        int op, x, y; i64 k;
        cin >> op;
        if(op == 1) {
            cin >> x >> y >> k;
            update2(1, 1, n, x, y, k);
        } else {
            cin >> x >> y;
            cout << query2(1, 1, n, x, y) << endl;
        }
    }
    return 0;
}
