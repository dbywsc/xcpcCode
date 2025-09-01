//0-base
//维护树上路径中的最小边
struct LCA {
    int n, LOG;
    std::vector<int> dep;
    std::vector<std::vector<int>> up;
    std::vector<std::vector<int>> minw;
    std::vector<std::vector<PII>> adj;
    LCA(int n_) : n(n_) {
        LOG = 0;
        while ((1 << LOG) <= n) LOG++;
        dep.assign(n, 0);
        up.assign(LOG, std::vector<int>(n, -1));
        adj.assign(n, std::vector<PII>());
        minw.assign(LOG, std::vector<int>(n, INF));
    }
    void add(int u, int v, int w) {
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }
    void dfs(int v, int p, int w) {
        up[0][v] = p;
        minw[0][v] = (p == -1 ? INF : w);
        for (int i = 1; i < LOG; i++) {
            if (up[i - 1][v] != -1) {
                up[i][v] = up[i - 1][up[i - 1][v]];
                minw[i][v] = std::min(minw[i - 1][v], minw[i - 1][up[i - 1][v]]);
            } else {
                up[i][v] = -1;
                minw[i][v] = INF;
            }
        }
        for (auto [to, w] : adj[v]) {
            if (to == p) continue;
            dep[to] = dep[v] + 1;
            dfs(to, v, w);
        }
    }
    //加完边再初始化
    void init(int root = 0) {
        for(int i = 1; i <= n; i++) {
            if(up[0][i] == -1) {
                dep[i] = 0;
                dfs(i, -1, INF);
            }
        }
    }
    //返回路径上的最小边权
    int query(int u, int v) {
        if (dep[u] < dep[v]) std::swap(u, v);
        int res = INF;
        int diff = dep[u] - dep[v];
        for (int i = 0; i < LOG; i++) {
            if (diff & (1 << i)) {
                res = std::min(res, minw[i][u]);
                u = up[i][u];
                if (u == -1) break;
            }
        }
        if (u == v) return res;
        for (int i = LOG - 1; i >= 0; i--) {
            if (up[i][u] != up[i][v]) {
                res = std::min(res, minw[i][u]);
                res = std::min(res, minw[i][v]);
                u = up[i][u];
                v = up[i][v];
            }
        }
        res = std::min(res, minw[0][u]);
        res = std::min(res, minw[0][v]);
        return res;
    }
};