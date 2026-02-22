void solve(void) {
    int n, m;
    std::cin >> n >> m;
    std::vector G(n + 1, std::vector<int>());
    std::vector<int> in(n + 1), out(n + 1), cur(n + 1);
    for (int i = 1; i <= m; i++) {
        int u, v; 
        std::cin >> u >> v;
        G[u].push_back(v);
        in[v]++;
        out[u]++;
    }
    int lar = 0;
    for (int i = 1; i <= n; i++) {
        std::sort(G[i].begin(), G[i].end());
        if (std::abs(out[i] - in[i]) > 1) {
            std::cout << "No\n";
            return;
        }
        if (out[i] > in[i]) {
            if (lar) {
                std::cout << "No\n";
                return;
            } else lar = i;
        }
    }
    std::vector<int> ans;
    auto dfs = [&](auto && self, int u) -> void {
        for (int &i = cur[u]; i < G[u].size(); ) {
            int v = G[u][i];
            i++;
            self(self, v);
        }
        ans.push_back(u);
    };
    dfs(dfs, lar ? lar : 1);
    if (ans.size() != m + 1) {
        std::cout << "No\n";
        return;
    }
    std::reverse(ans.begin(), ans.end());
    for (auto i : ans) std::cout << i << ' ';
}
