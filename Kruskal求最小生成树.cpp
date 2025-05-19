#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
int n, m;
int p[N];
struct Edge {
    int u, v, w;
    bool operator< (const Edge &W) const {
        return w < W.w;
    }
}edges[N];
int res,cnt;
int find(int x) {
    if(p[x] != x) p[x] = find(p[x]);
    return p[x];
}
int main(void) {
    cin >> n >> m;
    for(int i = 1; i <= m; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }
    sort(edges + 1, edges + 1 + m);
    for(int i = 1; i <= n; i++) p[i] = i;
    for(int i = 1; i <= m; i++) {
        int u = edges[i].u, v = edges[i].v, w = edges[i].w;
        u = find(u), v = find(v);
        if(u != v) {
            p[u] = v;
            res += w;
            cnt ++;
        }
    }
    if(cnt  < n - 1) cout << "impossible" << endl;
    else cout << res << endl;
}
