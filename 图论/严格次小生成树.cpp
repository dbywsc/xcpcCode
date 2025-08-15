#include <bits/stdc++.h>
#define x first
#define y second
#define INF 0x3f3f3f3f
using namespace std;
using i64 = long long;
const int N = 3e5 + 10;
int n, m;
struct Edge {
    int a, b, w;
    bool used;
    bool operator<(const Edge &t) const {
        return w < t.w;
    }
}edge[N];
int p[N];
typedef pair<int, int> PII;
vector<PII> G[N];
int depth[N], fa[N][17], d1[N][17], d2[N][17];
int find(int x) {
    if(p[x] != x) p[x] = find(p[x]);
    return p[x];
}
i64 kruskal(void) {
    for(int i = 1; i <= n; i++) p[i] = i;
    sort(edge, edge + m);
    i64 res = 0;
    for(int i = 0; i < m; i++) {
        int a = find(edge[i].a), b = find(edge[i].b), w = edge[i].w;
        if(a != b) {
            p[a] = b;
            res += w;
            edge[i].used = true;
        }
    }
    return res;
}
void build(void) {
    for(int i = 0; i < m; i++) {
        if(edge[i].used) {
            int a = edge[i].a, b = edge[i].b, w = edge[i].w;
            G[a].emplace_back(b, w); G[b].emplace_back(a, w);
        }
    }
}
void bfs(void) {
    memset(depth, 0x3f, sizeof(depth));
    depth[0] = 0, depth[1] = 1;
    queue<int> q; q.push(1);
    while(q.size()) {
        auto u = q.front(); q.pop();
        for(auto ed : G[u]) {
            int v = ed.x, w = ed.y;
            if(depth[v] > depth[u] + 1) {
                depth[v] = depth[u] + 1;
                q.push(v);
                fa[v][0] = u;
                d1[v][0] = w, d2[v][0] = -INF;
                for(int k = 1; k <= 16; k++) {
                    int anc = fa[v][k - 1];
                    fa[v][k] = fa[anc][k - 1];
                    int distance[4] = {d1[v][k - 1], d2[v][k - 1], d1[anc][k - 1], d2[anc][k - 1]};
                    d1[v][k] = d2[v][k] = -INF;
                    for(int i = 0; i < 4; i++) {
                        int d = distance[i];
                        if(d > d1[v][k]) d2[v][k] = d1[v][k], d1[v][k] = d;
                        else if(d != d1[v][k] && d > d2[v][k]) d2[v][k] = d;
                    }
                }
            }
        }
    }
}
int lca(int a, int b, int w) {
    if(depth[a] < depth[b]) swap(a, b);
    int distance[N * 2];
    int cnt = 0;
    for(int k = 16; k >= 0; k--) {
        if(depth[fa[a][k]] >= depth[b]) {
            distance[cnt++] = d1[a][k];
            distance[cnt++] = d2[a][k];
            a = fa[a][k];
        }
    }
    if(a != b) {
        for(int k = 16; k >= 0; k--) {
            if(fa[a][k] != fa[b][k]) {
                distance[cnt++] = d1[a][k];
                distance[cnt++] = d2[a][k];
                distance[cnt++] = d1[b][k];
                distance[cnt++] = d2[b][k];
                a = fa[a][k], b = fa[b][k];
            }
        }
        distance[cnt++] = d1[a][0];
        distance[cnt++] = d1[b][0];
    }
    int dist1 = -INF, dist2 = -INF;
    for(int i = 0; i < cnt; i++) {
        int d = distance[i];
        if(d > dist1) dist2 = dist1, dist1 = d;
        else if(d != dist1 && d > dist2) dist2 = d;
    }
    if(w > dist1) return w - dist1;
    if(w > dist2) return w - dist2;
    return INF;
}
int main(void) {
    cin >> n >> m;
    for(int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        edge[i] = {a, b, c};
    }
    i64 sum = kruskal();
    build(); bfs();
    i64 res = 1e18;
    for(int i = 0; i < m; i++) {
        if(!edge[i].used) {
            int a = edge[i].a, b = edge[i].b, w = edge[i].w;
            res = min(res, sum + lca(a, b, w));
        }
    }
    cout << res << endl;
    return 0;
}
