std::vector<int> dfn, son, p, dep, seg, siz, top;

struct SegTree {
    const int INF = 1e9;
    int n;
    std::vector<int> max, tag, sum;
    SegTree(int n_): n(n_) {
        max.assign(4 * n, 0);
        tag.assign(4 * n, 0);
        sum.assign(4 * n, 0);
    }
    void pull(int o) {
        max[o] = std::max(max[o * 2], max[o * 2 + 1]);
        sum[o] = (sum[o * 2] + sum[o * 2 + 1]) % M;
    }
    void apply(int o, int l, int r, int v) {
        tag[o] += v;
        max[o] += v;
        sum[o] = (sum[o] + v *  (r - l + 1)) % M;
    }
    void push(int o, int l, int r) {
        if(tag[o] != 0) {
            int m = (l + r) / 2;
            apply(o * 2, l, m, tag[o]);
            apply(o * 2 + 1, m + 1, r, tag[o]);
            tag[o] = 0;
        }
    }
    void build(int o, int l, int r, const std::vector<int> &a) {
        tag[o] = 0;
        if(l == r) {
            max[o] = a[seg[l]];
            sum[o] = a[seg[l]] % M;
            return;
        }
        int m = (l + r) / 2;
        build(o * 2, l, m, a);
        build(o * 2 + 1, m + 1, r, a);
        pull(o);
    }
    void build(const std::vector<int> &a) {
        build(1, 1, n, a);
    }
    int query(int o, int l, int r, int L, int R) {
        if(R < l || r < L) return 0;
        if(L <= l && r <= R) return sum[o] % M;
        push(o, l, r);
        int m = (l + r) / 2;
        return (query(o * 2, l, m, L, R) + query(o * 2 + 1, m + 1, r, L, R)) % M;
    }
    int query(int x, int y) {
        return query(1, 1, n, x, y);
    }
    void add(int o, int l, int r, int L, int R, int v) {
        if(R < l || r < L) return;
        if(L <= l && r <= R) {
            apply(o, l, r, v);
            return;
        }
        push(o, l, r);
        int m = (l + r) / 2;
        add(o * 2, l, m, L, R, v);
        add(o * 2 + 1, m + 1, r, L, R, v);
        pull(o);
    }
    void add(int x, int y, int v) {
        add(1, 1, n, x, y, v);
    }
};
auto dfs1 = [&](auto && self, int u, int fa) -> void {
    p[u] = fa;
    dep[u] = dep[fa] + 1;
    siz[u] = 1;
    for(auto v : G[u]) {
        if(v == fa) continue;
        self(self, v, u);
    }
    for(auto v : G[u]) {
        if(v == fa) continue;
        siz[u] += siz[v];
        if(son[u] == 0 || siz[son[u]] < siz[v]) son[u] = v;
    }
};
auto dfs2 = [&](auto && self, int u, int t) -> void {
    top[u] = t;
    dfn[u] = ++cntd;
    seg[cntd] = u;
    if(son[u] == 0) return;
    self(self, son[u], t);
    for(auto v : G[u]) {
        if(v == p[u] || v == son[u]) continue;
        self(self, v, v);
    }
};
dfs1(dfs1, r, 0);
dfs2(dfs2, r, r);
SegTree st(n);
st.build(a);
auto pathUpdate = [&](int u, int v, int w) -> void {
    while(top[u] != top[v]) {
        if(dep[top[u]] < dep[top[v]]) std::swap(u, v);
        st.add(dfn[top[u]], dfn[u], w);
        u = p[top[u]];
    }
    if(dep[u] > dep[v]) std::swap(u, v);
    st.add(dfn[u], dfn[v], w);
};
auto pathQuery = [&](int u, int v) -> int {
    int res = 0;
    while(top[u] != top[v]) {
        if(dep[top[u]] < dep[top[v]]) std::swap(u, v);
        res = (res + st.query(dfn[top[u]], dfn[u])) % M;
        u = p[top[u]];
    }
    if(dep[u] > dep[v]) std::swap(u, v);
    res = (res + st.query(dfn[u], dfn[v])) % M;
    return res;
};
auto subTreeUpdate = [&](int u, int w) -> void {
    return st.add(dfn[u], dfn[u] + siz[u] - 1, w);
};
auto subTreeQuery = [&](int u) -> int {
    return st.query(dfn[u], dfn[u] + siz[u] - 1);
};
