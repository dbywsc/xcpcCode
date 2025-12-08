struct SegTree {
    int n;
    std::vector<int> maxn, minn;
    SegTree(int n_): n(n_), maxn(4 * n + 1), minn(4 * n + 1) {}
    void pull(int o) {
        maxn[o] = std::max(maxn[o * 2], maxn[o * 2 + 1]);
        minn[o] = std::min(minn[o * 2], minn[o * 2 + 1]);
    }
    void build(int o, int l, int r, const std::vector<int> &a) {
        if(l == r) {
            maxn[o] = a[l];
            minn[o] = a[l];
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
    void change(int o, int l, int r, int p, int v) {
        if(l == r) {
            maxn[o] = minn[o] = v;
            return;
        }
        int m = (l + r) / 2;
        if(p <= m) change(o * 2, l, m, p, v);
        else change(o * 2 + 1, m + 1, r, p, v);
        pull(o);
    }
    void change(int p, int v) {
        change(1, 1, n, p, v);
    }
    int query_max(int o, int l, int r, int x, int y) {
        if(x <= l && r <= y) return maxn[o];
        if(y < l || r < x) return -INF;
        int m = (l + r) / 2;
        return std::max(query_max(o * 2, l, m, x, y), query_max(o * 2 + 1, m + 1, r, x, y));
    }
    int query_max(int x, int y) {
        return query_max(1, 1, n, x, y);
    }
    int query_min(int o, int l, int r, int x, int y) {
        if(x <= l && r <= y) return minn[o];
        if(y < l || r < x) return INF;
        int m = (l + r) / 2;
        return std::min(query_min(o * 2, l, m, x, y), query_min(o * 2 + 1, m + 1, r, x, y));
    }
    int query_min(int x, int y) {
        return query_min(1, 1, n, x, y);
    }
};
