#include <bits/stdc++.h>
#define x first
#define y second
using namespace std;
typedef pair<int, int> PII;
const int N = 5e5 + 10;
int n, s, far;
int dis[N], f[N], flag[N];
vector<PII> G[N];
void dfs(int u, int fa) {
	f[u] = fa;
	if(dis[u] > dis[far]) far = u;
	for(auto ed : G[u]) {
		int v = ed.x, w = ed.y;
		if(v == fa || flag[v]) continue;
		dis[v] = dis[u] + w;
		dfs(v, u);
	}
}
int main(void) {
	cin >> n;
	for(int i = 1; i < n; i++) {
		int u, v, w; cin >> u >> v >> w;
		G[u].emplace_back(v, w); G[v].emplace_back(u, w);
	}
	int A, B;
	dis[1] = 1; dfs(1, 0); A = far;
	dis[far] = 0; dfs(far, 0); B = far;
	cout << dis[B] << endl;
	return 0;
}

#include <bits/stdc++.h>
#define endl '\n'
using namespace std;
const int N = 2e5 + 10;
vector<int> G[N];
int n;
int ans = 0;
bool root[N];
int d1[N], d2[N];
void dfs(int u, int fa) {
    d1[u] = d2[u] = 0;
    for(int v : G[u]) {
        if(v == fa) continue;
        dfs(v, u);
        int t = d1[v] + 1;
        if(t > d1[u]) d2[u] = d1[u], d1[u] = t;
        else if(t > d2[u]) d2[u] = t;
    }
    ans = max(ans, d1[u] + d2[u]);
}
void solve(void) {
    memset(G, 0, sizeof(G));
    memset(root, 0, sizeof(root));
    cin >> n;
    for(int i= 1; i < n; i++) {
        int u, v; cin >> u >> v;
        G[u].push_back(v); G[v].push_back(u);
        root[v] = 1;
    }
    ans = 0;
    int r = 0;
    for(int i = 0; i < n; i++) if(!root[i]) {
        r = i; break;
    }
    dfs(1, 0);
    cout << ans << endl;
}
int main(void) {
    cin.tie(0); cout.tie(0);
    ios::sync_with_stdio(false);
    int t = 1;
    //cin >> t;
    while(t--) solve();
    return 0;
}
