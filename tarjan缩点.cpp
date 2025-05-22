#include <bits/stdc++.h>
using namespace std;
const int N = 1e4 + 10;
int dfn[N], low[N], siz[N], id[N], w[N], in[N];
int timestamp, cnt;
bool st[N];
vector<int> G[N];
vector<int> g[N];
stack<int> s;
int dis[N];
int n, m, ans;
void tarjan(int u) {
    low[u] = dfn[u] = ++timestamp; st[u] = 1; s.push(u);
    for(auto v : G[u]) {
        if(!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if(st[v]) {
            low[u] = min(low[u], dfn[v]);
        }
    }
    if(low[u] == dfn[u]) {
        int y; cnt++;
        do {
            y = s.top(); s.pop(); st[y] = 0;
            id[y] = cnt;
            siz[cnt] += w[y];
        } while(y != u);
    }
}
void topo(void) {
    queue<int> q;
    for(int i = 1; i <= cnt; i++) {
        if(!in[i]) q.push(i);
        dis[i] = siz[i];
    }
    while(q.size()) {
        int u = q.front(); q.pop();
        for(auto v : g[u]) {
            dis[v] = max(dis[v], dis[u] + siz[v]);
            in[v]--;
            if(!in[v]) q.push(v);
        }
    }
}
int main(void) {
    cin >> n >> m;
    for(int i = 1; i <= n; i++) cin >> w[i];
    for(int i = 1; i <= m; i++) {
        int u, v; cin >> u >> v;
        G[u].push_back(v);
    }
    for(int i = 1; i <= n; i++) if(!dfn[i]) tarjan(i);
    for(int i = 1; i <= n; i++) {
        for(auto j : G[i]) {
            if(id[j] != id[i]) g[id[i]].push_back(id[j]), in[id[j]]++;
        }
    }
    topo();
    for(int i = 1; i <= cnt; i++) ans = max(ans, dis[i]);
    cout << ans << endl;
    return 0;
}
