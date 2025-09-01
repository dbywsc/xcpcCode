//0-base
struct LCA {
    int n, LOG;
    std::vector<int> dep;
    std::vector<std::vector<int>> up;
    std::vector<std::vector<int>> adj;
    LCA(int n_) : n(n_) {
        LOG = 0;
        while ((1 << LOG) <= n) LOG++;
        dep.assign(n, 0);
        up.assign(LOG, std::vector<int>(n, -1));
        adj.assign(n, std::vector<int>());
    }
    void add(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    void dfs(int v, int p) {
        up[0][v] = p;
        for (int i = 1; i < LOG; i++) {
            if (up[i - 1][v] != -1) {
                up[i][v] = up[i - 1][up[i - 1][v]];
            } else {
                up[i][v] = -1;
            }
        }
        for (auto to : adj[v]) {
            if (to == p) continue;
            dep[to] = dep[v] + 1;
            dfs(to, v);
        }
    }
    //加完边再初始化
    void init(int root = 0) {
        dfs(root, -1);
    }
    int query(int u, int v) {
        if (dep[u] < dep[v]) std::swap(u, v);
        int diff = dep[u] - dep[v];
        for (int i = 0; i < LOG; i++) {
            if (diff & (1 << i)) {
                u = up[i][u];
                if (u == -1) break;
            }
        }
        if (u == v) return u;
        for (int i = LOG - 1; i >= 0; i--) {
            if (up[i][u] != up[i][v]) {
                u = up[i][u];
                v = up[i][v];
            }
        }
        return up[0][u];
    }
};