#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
const int N = 5e5 + 10;
int a[N], w[N * 4];
int n;
void Init_hash(void) {
    int tmp[N];
    for(int i = 1; i <= n; i++) tmp[i] = a[i];
    sort(tmp + 1, tmp + 1 + n);
    int *ed = unique(tmp + 1, tmp + 1 + n);
    for(int i = 1; i <= n; i++) a[i] = lower_bound(tmp + 1, ed, a[i]) - tmp;
}
void update(int u, int L, int R, int v) {
    w[u]++;
    if(L == R) return;
    int M = (L + R) / 2;
    if(M >= v) update(u * 2, L, M, v);
    else update(u * 2 + 1, M + 1, R, v);
}
int query(int u, int L, int R, int v) {
    if(w[u] == 0) return 0;
    if(L >= v) return w[u];
    int M = (L + R) / 2;
    if(M < v) return query(u * 2 + 1, M + 1, R, v);
    return query(u * 2 + 1, M + 1, R, v) + query(u * 2, L, M, v);
}
int main(void) {
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> a[i];
    Init_hash();
    i64 ans = 0;
    for(int j = 1; j <= n; j++) {
        ans += query(1, 1, n, a[j] + 1);
        update(1, 1, n, a[j]);
    }
    cout << ans << endl;
    return 0;
}
