struct KruskalTree {
    DSU dsu;
    std::vector<int> lc, rc, val;
    int idx;
    std::vector<std::vector<int>> fa;
    std::vector<int> dep;
    int lg;

    KruskalTree(const std::vector<Edge> &edges, int n)
        : lc(2 * n + 1), rc(2 * n + 1), val(2 * n + 1), idx(n), dsu(2 * n), dep(2 * n + 1) {
            lg = std::__lg(2 * n + 1);
            fa.assign(2 * n + 1, std::vector<int>(lg + 1, 0));
            auto e = edges;
            std::sort(e.begin(), e.end(), [&](Edge x, Edge y) {
                return x.w < y.w;
            });
            for(auto &[u, v, w] : e) {
                if(!dsu.same(u, v)) {
                    idx++;
                    int ru = dsu.find(u);
                    int rv = dsu.find(v);
                    lc[idx] = ru;
                    rc[idx] = rv;
                    dsu.p[ru] = idx;
                    dsu.p[rv] = idx;
                    val[idx] = w;
                }
                if(idx == 2 * n + 1) break;
            }
            auto dfs = [&](auto && self, int u, int parent) -> void {
                fa[u][0] = parent;
                for(int i = 1; i <= lg; i++) {
                    fa[u][i] = fa[fa[u][i - 1]][i - 1];
                }
                if(lc[u]) {
                    dep[lc[u]] = dep[u] + 1;
                    self(self, lc[u], u);
                }
                if(rc[u]) {
                    dep[rc[u]] = dep[u] + 1;
                    self(self, rc[u], u);
                }
            };
            for(int i = idx; i >= 1; i--) {
                if(!dep[i]) {
                    dep[i] = 1;
                    dfs(dfs, i, 0);
                }
            }
        }
    int getLca(int u, int v) {
        if(dep[u] < dep[v]) std::swap(u, v);
        for(int i = lg; i >= 0; i--) {
            if(dep[fa[u][i]] >= dep[v]) u = fa[u][i];
        }
        if(u == v) return u;
        for(int i = lg; i >= 0; i--) {
            if(fa[u][i] != fa[v][i]) {
                u = fa[u][i];
                v = fa[v][i];
            }
        }
        return fa[u][0];
    }
    int getVal(int x) {
        return val[x];
    }
    bool isConnected(int u, int v) {
        return dsu.same(u, v);
    }
    int queryMaxEdge(int u, int v) {
        if(!isConnected(u, v)) return -1;
        return getVal(getLca(u, v));
    }
};
