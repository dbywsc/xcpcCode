#include <bits/stdc++.h>
#define x first
#define y second
using namespace std;
const int N = 5e3 + 10;
int n, m;
typedef pair<int, int> PII;
vector<PII> G[N];
int dis[N], cnt[N];
bool st[N];
bool spfa(void) {
    queue<int> q;
    memset(dis, 0x3f, sizeof(dis));
    dis[0] = 0; q.push(0); st[0] = 1;
    while(q.size()) {
        auto u = q.front(); q.pop();
        st[u] = 0;
        for(auto ed : G[u]) {
            int v = ed.x, w = ed.y;
            if(dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                cnt[v] = cnt[u] + 1;
                if(cnt[v] >= n + 1) return false;
                if(!st[v]) {
                    st[v] = 1;
                    q.push(v);
                }
            }
        }
    }
    return true;
}
int main(void) {
    cin >> n >> m;
    for(int i = 1; i <= n; i++) G[0].emplace_back(i, 0);
    while(m--) {
        int u, v, w;
        cin >> u >> v >> w;
        G[v].emplace_back(u, w);
    }
    if(!spfa()) cout << "NO" << endl;
    else for(int i = 1; i <= n; i++) cout << dis[i] << " ";
    return 0;
}
