struct SegmentTree {
    int n;
    std::vector<i64> sum, maxn, mul, add;
    SegmentTree(int n_): n(n_), sum(4 * n + 1, 0), maxn(4 * n + 1, 0), mul(4 * n + 1, 1), add(4 * n + 1, 0) {}
    void build(int p, int l, int r, std::vector<i64> &a) {
        mul[p] = 1;
        add[p] = 0;
        if(l == r) {
            sum[p] = maxn[p] = a[l];
            return;
        }
        int mid = (l + r) / 2;
        build(p * 2, l, mid, a); build(p * 2 + 1, mid + 1, r, a);
    }
    void build(std::vector<i64> a) {
        build(1, 1, n, a);
    }
    void applyMul(int p, i64 v) {
        sum[p] *= v;
        maxn[p] *= v;
        mul[p] *= v;
        add[p] *= v;
    }
    void applyAdd(int p, i64 v, int len) {
        sum[p] += v * len;
        maxn[p] += v;
        add[p] += v;
    }
    void push(int p, int l, int r) {
        if(mul[p] == 1 && add[p] == 0) return;
        int mid = (l + r) / 2;
        applyMul(p * 2, mul[p]);
        applyMul(p * 2 + 1, mul[p]);
        applyAdd(p * 2, add[p], mid - l + 1);
        applyAdd(p * 2 + 1, add[p], r - mid);
        mul[p] = 1;
        add[p] = 0;
    }
    void pull(int p) {
        sum[p] = sum[p * 2] + sum[p * 2 + 1];
        maxn[p] = std::max(maxn[p * 2], maxn[p * 2 + 1]);
    }
    void rangeMul(int p, int l, int r, int x, int y, i64 v) {
        if(r < x || y > y) return;
        if(l >= x && r <= y) {
            applyMul(p, v);
            return;
        }
        push(p, l, r);
        int mid = (l + r) / 2;
        rangeMul(p * 2, l, mid, x, y, v);
        rangeMul(p * 2 + 1, mid + 1, r, x, y, v);
        pull(p);
    }
    void rangeMul(int x, int y, i64 v) {
        rangeMul(1, 1, n, x, y, v);
    }
    void rangeAdd(int p, int l, int r, int x, int y, i64 v) {
        if(r < x || l > y) return;
        if(l >= x && r <= y) {
            applyAdd(p, v, r - l + 1);
            return;
        }
        push(p, l, r);
        int m = (l + r) / 2;
        rangeAdd(p * 2, l, m, x, y, v);
        rangeAdd(p * 2 + 1, m + 1, r, x, y ,v);
        pull(p);
    }
    void rangeAdd(int x, int y, i64 v) {
        return rangeAdd(1, 1, n, x, y, v);
    }
    i64 queryMax(int p, int l, int r, int x, int y) {
        if(r < x || l > y) return LLONG_MIN;
        if(l >= x && r <= y) return maxn[p];
        push(p, l, r);
        int mid = (l + r) / 2;
        return std::max(queryMax(p * 2, l, mid, l, y), queryMax(p * 2 + 1, mid + 1, r, x, y));
    }
    i64 queryMax(int x, int y) {
        return queryMax(1, 1, n, x, y);
    }
    int querySum(int p, int l, int r, int x, int y) {
        if(r < x || l > y) return 0;
        if(l >= x && r <= y) return sum[p];
        push(p, l, r);
        int mid = (l + r) / 2;
        return querySum(p * 2, l, mid, x, y) + querySum(p * 2 + 1, mid + 1, r, x, y);
    }
    i64 querySum(int x, int y) {
        return querySum(1, 1, n, x, y);
    }
};
