//P3275
//关于SPFA，___
#include <bits/stdc++.h>
#define x first
#define y second
using namespace std;
const int N = 1e5 + 10, M = N * 3;
int tle = 9999999;
typedef pair<int, int> PII;
using i64 = long long;
int n, m;
int h[N], e[M], w[M], ne[M], idx;
int dis[N];
int cnt[N];
bool st[N];
void add(int a, int b, int c) {
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}
bool spfa(void) {
    int istle = 0;
    stack<int> q;
    memset(dis, -0x3f, sizeof(dis));
    dis[0] = 0; q.push(0); st[0] = 1;
    while(q.size()) {
        auto u = q.top(); q.pop();
        st[u] = 0;
        for(int i = h[u]; ~i; i = ne[i]) {
            int v = e[i];
            if(dis[v] < dis[u] + w[i]) {
                istle++;
                dis[v] = dis[u] + w[i];
                cnt[v] = cnt[u] + 1;
                if(cnt[v] >= n + 1 || istle >= tle) return false;
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
    memset(h, 0xff, sizeof(h));
    cin >> n >> m;
    for(int i = 1; i <= m; i++) {
        int x, a, b; cin >> x >> a >> b;
        if(x == 1) add(a, b, 0), add(b, a, 0);
        else if(x == 2) add(a, b, 1);
        else if(x == 3) add(b, a, 0);
        else if(x == 4) add(b, a, 1);
        else add(a, b, 0);
    }
    for(int i = 1; i <= n; i++) add(0, i, 1);
    if(!spfa()) cout << -1 << endl;
    else {
        i64 res = 0;
        for(int i = 1;  i <= n;i ++) res += dis[i];
        cout << res << endl;
    }
    return 0;
}
