struct SegTree {
    int n;
    std::vector<int> max, tag;
    SegTree(int n_): n(n_) {
        max.assign(4 * n, 0);
        tag.assign(4 * n, 0);
    }
    void pull(int o) {
        max[o] = std::max(max[o * 2], max[o * 2 + 1]);
    }
    void apply(int o, int l, int r, int v) {
        tag[o] += v;
        max[o] += v;
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
            max[o] = a[l];
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
        if(R < l || r < L) return -INF;
        if(L <= l && r <= R) return max[o];
        push(o, l, r);
        int m = (l + r) / 2;
        return std::max(query(o * 2, l, m, L, R), query(o * 2 + 1, m + 1, r, L, R));
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
