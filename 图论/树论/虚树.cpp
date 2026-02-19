    std::vector G(n + 1, std::vector<int>());
    std::vector vG(n + 1, std::vector<int>());

    for (int i = 1; i < n; i++) {
        int u, v; std::cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    std::vector<int> dfn(n + 1), dep(n + 1);
    std::vector stTable(n + 1, std::vector<int>(21));
    int timestamp = 0;
    auto dfs = [&](auto && self, int u, int fa) -> void {
        dfn[u] = ++timestamp;
        dep[u] = dep[fa] + 1;
        stTable[u][0] = fa;
        for (int p = 1; p <= 20; p++) {
            stTable[u][p] = stTable[stTable[u][p - 1]][p - 1];
        }
        for (auto v : G[u]) {
            if (v == fa) continue;
            self(self, v, u);
        }
    };
    dfs(dfs, 1, 0);
    auto getLca = [&](int a, int b) -> int {
        if (dep[a] < dep[b]) std::swap(a, b);
        for (int p = 20; p >= 0; p--) {
            if (dep[stTable[a][p]] >= dep[b]) a = stTable[a][p];
        }
        if (a == b) return a;
        for (int p = 20; p >= 0; p--) {
            if (stTable[a][p] != stTable[b][p]) {
                a = stTable[a][p];
                b = stTable[b][p];
            }
        }
        return stTable[a][0];
    };
    std::vector<int> a;
    auto build = [&](void) -> int {
        std::sort(a.begin() + 1, a.end(), [&](int x, int y) {
            return dfn[x] < dfn[y];
        });
        std::vector<int> tmp;
        for (int i = 1; i < a.size() - 1; i++) {
            tmp.push_back(a[i]);
            tmp.push_back(getLca(a[i], a[i + 1]));
        }
        tmp.push_back(a.back());
        std::sort(tmp.begin(), tmp.end(), [&](int x, int y) {
            return dfn[x] < dfn[y];
        });
        tmp.erase(std::unique(tmp.begin(), tmp.end()), tmp.end());
        for (auto i : tmp) vG[i].clear();
        for (int i = 0; i < tmp.size() - 1; i++) {
            int u = getLca(tmp[i], tmp[i + 1]);
            int v = tmp[i + 1];
            vG[u].push_back(v);
            vG[v].push_back(u);
        }
        return tmp[0];
    };
