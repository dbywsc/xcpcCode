struct SegTree {
    int n;
    std::vector<int> xsum, tag;
    SegTree(int n_): n(n_) {
        tag.assign(4 * n, 0);
        xsum.assign(4 * n, 0);
    }
    void pull(int o) {
        xsum[o] = xsum[o * 2] ^ xsum[o * 2 + 1];
    }
    void build(int o, int l, int r, const std::vector<int> &a) {
        if(l == r) {
            xsum[o] = a[l];
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
    void push(int o, int l, int r) {
        if(!tag[o]) return;
        int m = (l + r) / 2;
        int lenL = m - l + 1;
        int lenR = r - m;
        if(lenL & 1) xsum[o * 2] ^= tag[o];
        if(lenR & 1) xsum[o * 2 + 1] ^= tag[o];
        tag[o * 2] ^= tag[o];
        tag[o * 2 + 1] ^= tag[o];
        tag[o] = 0;
    }
    void update(int o, int l, int r, int x, int y, int v) {
        if(x <= l && r <= y) {
            if((r - l + 1) & 1) {
                xsum[o] ^= v;
            }
            tag[o] ^= v;
            return;
        }
        push(o, l, r);
        int m = (l + r) / 2;
        if(x <= m) update(o * 2, l, m, x, y, v);
        if(y > m) update(o * 2 + 1, m + 1, r, x, y, v);
        pull(o);
    }
    void update(int x, int y, int v) {
        update(1, 1, n, x, y, v);
    }
    int query(int o, int l, int r, int x, int y) {
        if(x <= l && r <= y) {
            return xsum[o];
        }
        push(o, l, r);
        int m = (l + r) / 2;
        int res = 0;
        if(x <= m) res ^= query(o, l, m, x, y);
        if(y > m) res ^= query(o, m + 1, r, x, y);
        return res;
    }
    int query(int x, int y) {
        return query(1, 1, n, x, y);
    }
};
