//本模板下标默认从1开始
struct SegTree {
    int n;
    std::vector<int> sum, tag;
    SegTree(int n_): n(n_) {
        sum.assign(4 * n, 0);
        tag.assign(4 * n, -1);
    }
    void pull(int o) {
        sum[o] = sum[o * 2] + sum[o * 2 + 1];
    }
    void apply(int o, int l, int r, int v) {
        sum[o] = v * (r - l + 1);
        tag[o] = v;
    }
    void push(int o, int l, int r) {
        if(tag[o] != -1) {
            int m = (l + r) / 2;
            apply(o * 2, l, m, tag[o]); 
            apply(o * 2 + 1, m + 1, r, tag[o]);
            tag[o] = -1;
        }
    }
    void build(int o, int l, int r, const std::vector<int> &a) {
        tag[o] = -1;
        if(l == r) {
            sum[o] = a[l];
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
        if(L <= l && r <= R) return sum[o];
        push(o, l, r);
        int m = (l + r) / 2;
        return query(o * 2, l, m, L, R) + query(o * 2 + 1, m + 1, r, L, R);
    }
    int query_sum(int x, int y) {
        return query(1, 1, n, x, y);
    }
    void update(int o, int l, int r, int L, int R, int v) {
        if(R < l || r < L) return;
        if(L <= l && r <= R) {
            apply(o, l, r, v);
            return;
        }
        push(o, l , r);
        int m = (l + r) / 2;
        update(o * 2, l, m, L, R, v);
        update(o * 2 + 1, m + 1, r, L, R, v);
        pull(o);
    }
    void update(int x, int y, int v) {
        update(1, 1, n, x, y, v);
    }
    int query(int o, int l, int r, int p) {
        if(l == r) return sum[o];
        push(o, l, r);
        int m = (l + r) / 2;
        if(p <= m) return query(o * 2, l, m, p);
        return query(o * 2 + 1, m + 1, r, p);
    }
    int query_point(int p) {
        return query(1, 1, n, p);
    }
};