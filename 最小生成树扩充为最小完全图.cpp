#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
struct edge {
    int a, b, w;
    bool operator<(const edge &W) const {
        return w < W.w;
    } 
}e[N];
int p[N], siz[N];
int n;
int find(int x) {
    if(x != p[x]) p[x] = find(p[x]);
    return p[x];
}
void solve(void) {
    cin >> n;
    for(int i = 1; i < n; i++) {
        cin >> e[i].a >> e[i].b >> e[i].w;
    }
    sort(e + 1, e + n);
    for(int i = 1; i <= n; i++) p[i] = i, siz[i] = 1;
    int res = 0;
    for(int i = 1; i < n; i++) {
        int a = find(e[i].a), b = find(e[i].b);
        if(a != b) {
            res += (siz[a] * siz[b] - 1) * (e[i].w + 1);
            siz[b] += siz[a];
            p[a] = b;
        }
    }
    cout << res << endl;
}
int main(void) {
    int t = 1;
    cin >> t;
    while(t--) solve();
    return 0;
}
