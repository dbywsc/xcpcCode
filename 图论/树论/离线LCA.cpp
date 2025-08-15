//树上两点间最近的距离：dis[a] + dis[b] - dis[lca(a, b}] * 2;
#include <bits/stdc++.h>
#define x first
#define y second
using namespace std;
const int N = 2e5 + 10;
typedef pair<int, int> PII;
vector<PII> G[N];
int p[N];       //LCA
int res[N];
int dis[N];
vector<PII> query[N];
int st[N];
int n, m;
void dfs(int u, int fa) {
    for(auto ed : G[u]) {
        int v = ed.x, w = ed.y;
        if(v == fa) continue;
        dis[v] = dis[u] + w;
        dfs(v, u);
    }
}
int find(int x) {
    if(p[x] != x) p[x] = find(p[x]);
    return p[x];
}
void tarjan(int u) {
    st[u] = 1;
    for(auto ed : G[u]) {
        int v = ed.x, w = ed.y;
        if(!st[v]) {
            tarjan(v);
            p[v] = u;
        }
    }
    for(auto item : query[u]) {
        int y = item.x, id = item.y;
        if(st[y] == 2) {
            int anc = find(y);
            res[id] = dis[u] + dis[y] - dis[anc] * 2;
        }
    }
    st[u] = 2;
}
int main(void) {
    cin >> n >> m;
    for(int i = 0; i < n - 1; i ++) {
        int u, v, w; cin >> u >> v >> w;
        G[u].emplace_back(v, w); G[v].emplace_back(u, w);
    }
    for(int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        if(a != b) {
            query[a].emplace_back(b, i);
            query[b].emplace_back(a, i);
        }
    }
    for(int i = 1; i <= n; i++) p[i] = i;
    dfs(1, -1);
    tarjan(1);
    for(int i = 0; i < m; i++) cout << res[i] << endl;
    return 0;
}
