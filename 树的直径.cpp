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
