#include <bits/stdc++.h>
#define v first
#define w second
#define INF INT_MAX
using namespace std;
const int N = 1e5 + 10;
typedef pair<int, int> PII;
vector<PII> G[N];
int n, m;
int dist[N];
bool st[N];
queue<int> q;
bool spfa(void) {
    fill(dist + 1, dist + 1 + n, INF);
    dist[1] = 0; st[1] = 1;
    q.push(1);
    while(q.size()) {
        auto u = q.front(); q.pop();
        st[u] = 0;
        for(auto ed : G[u]) {
            int v = ed.v, w = ed.w;
            if(dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                if(!st[v]) {st[v] = 1; q.push(v);}
            }
        }
    }
    if(dist[n] > INF / 2) return false;
    return true;
}
int main(void) {
    cin >> n >> m;
    for(int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        G[u].push_back({v, w});
    }
    if(spfa()) cout << dist[n];
    else cout << "impossible" << endl;
    return 0;
}
