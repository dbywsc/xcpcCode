#include <bits/stdc++.h>
using namespace std;
const int N = 510;
const int INF = 0x3f3f3f3f;
int G[N][N], n, m;
int dis[N];
bool st[N];
int prim(void) {
    memset(dis, 0x3f, sizeof(dis));
    int res = 0;
    for(int i = 0; i < n; i++) {
        int t = -1;
        for(int j = 1; j <= n; j++) {
            if(!st[j] && (t == -1 || dis[t] > dis[j])) {
                t = j;
            }
        }
        if(i) res += dis[t];
        if(i && dis[t] == INF) return INF;
        for(int j = 1; j <= n; j++) dis[j] = min(dis[j], G[t][j]);
        st[t] = true;
    }
    return res;
}
int main(void) {
    cin >> n >> m;
    memset(G, 0x3f, sizeof(G));
    for(int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        G[u][v] = G[v][u] = min(G[u][v], w);
    }
    int t = prim();
    if(t == INF) cout << "impossible";
    else cout << t << endl;
    return 0;
}
