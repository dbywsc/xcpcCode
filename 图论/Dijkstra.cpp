#include <bits/stdc++.h>
//#define int long long
#define x first
#define y second
#define endl '\n'
#define IOS std::ios::sync_with_stdio(false);
using namespace std;
typedef pair<int, int> PII;
const int N = 1e5 + 10;
const int INF = 0x3f3f3f3f;
int n, m;
vector<PII> G[N];
int dist[N];
bool st[N];
int dijkstra(void) {
    memset(dist, 0x3f, sizeof(dist));
    dist[1] = 0;
    priority_queue<PII, vector<PII>, greater<PII> > q;
    q.push({0, 1});
    while(q.size()) {
        auto u = q.top().y; q.pop();
        if(st[u]) continue;
        st[u] = 1;
        for(auto ed : G[u]) {
            int v = ed.x, w = ed.y;
            if(dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                q.push({dist[v], v});
            }
        }
    }
    return dist[n] == INF ? -1 : dist[n];
}
void solve(void) {
    cin >> n >> m;
    //memset(G, 0x3f, sizeof(G));
    for(int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        G[u].push_back({v, w});
    }
    cout << dijkstra() << endl;
}
signed main(void) {
    IOS;
    solve();
    return 0;
}
