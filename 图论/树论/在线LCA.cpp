#include <bits/stdc++.h>
using namespace std;
const int N = 40010;
vector<int> G[N];
int n, m;
int depth[N], fa[N][16];
void bfs(int root) {
    memset(depth, 0x3f, sizeof(depth));
    depth[0] = 0, depth[root] = 1;
    queue<int> q; q.push(root);
    while(q.size()) {
        auto u = q.front(); q.pop();
        for(auto v : G[u]) {
            if(depth[v] > depth[u] + 1) {
                depth[v] = depth[u] + 1;
                q.push(v);
                fa[v][0] = u;
                for(int k = 1; k <= 15; k++) {
                    fa[v][k] = fa[fa[v][k - 1]][k - 1];
                }
            }
        }
    }
}
int lca(int a, int b) {
    if(depth[a] < depth[b]) swap(a, b);
    for(int k = 15; k >= 0; k--) {
        if(depth[fa[a][k]] >= depth[b]) a = fa[a][k];
    }
    if(a == b) return a;
    for(int k = 15; k >= 0; k--) {
        if(fa[a][k] != fa[b][k]) {
            a = fa[a][k];
            b = fa[b][k];
        }
    }
    return fa[a][0];
}
int main(void) {
    cin >> n;
    int root = 0;
    for(int i = 0; i < n; i++) {
        int u, v; cin >> u >> v;
        if(v == -1) root = u;
        else G[u].push_back(v), G[v].push_back(u);
    }
    bfs(root);
    cin >> m;
    while(m--) {
        int a, b; cin >> a >> b;
        int p = lca(a, b);
        if(p == a) cout << 1 << endl;
        else if(p == b) cout << 2 << endl;
        else cout << 0 << endl;
    }
    return 0;
}
