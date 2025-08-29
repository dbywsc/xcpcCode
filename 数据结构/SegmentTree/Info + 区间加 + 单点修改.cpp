//本模板下标从0开始
struct Info {
    i64 sum;
    int len;
    Info(): sum(0), len(0) {}
    Info(i64 x): sum(x), len(1) {}
    Info(i64 s, int l): sum(s), len(l) {}
    friend Info operator+(const Info &A, const Info &B) {
        return Info(A.sum + B.sum, A.len + B.len);
    }
};
struct SegmentTree {
    int n;
    std::vector<i64> tag;
    std::vector<Info> info;
    SegmentTree(int n_) : n(n_), tag(4 * n), info(4 * n) {};
    void pull(int p) {
        info[p] = info[2 * p] + info[2 * p + 1];
    } 
    void add(int p, i64 v) {
        tag[p] += v;
        info[p].sum += v * info[p].len;
    }
    void push(int p) {
        add(2 * p, tag[p]);
        add(2 * p + 1, tag[p]);
        tag[p] = 0;
    }
    void build(int p, int l, int r, const std::vector<i64> &a) {
        if(r - l == 1) {
            info[p] = Info(a[l]);
            return;
        }
        int m = (l + r) / 2;
        build(2 * p, l, m, a);
        build(2 * p + 1, m, r, a);
        pull(p);
    }
    void build(const std::vector<i64> &a) {
        build(1, 0, n, a);
    }
    Info query(int p, int l, int r, int x, int y) {
        if(l >= y || r <= x) {
            return {};
        }
        if(l >= x && r <= y) {
            return info[p];
        }
        int m = (l + r) / 2;
        push(p);
        return query(2 * p, l, m, x, y) + query(2 * p + 1, m, r, x, y);
    }
    Info query(int x, int y) {
        return query(1, 0, n, x, y);
    }
    void rangeAdd(int p, int l, int r, int x, int y, i64 v) {
        if(l >= y || r <= x) return;
        if(l >= x && r <= y) return add(p, v);
        int m = (l + r) / 2;
        push(p);
        rangeAdd(2 * p, l, m, x, y, v);
        rangeAdd(2 * p + 1, m, r, x, y, v);
        pull(p);
    }
    void rangeAdd(int x, int y, i64 v) {
        rangeAdd(1, 0, n, x, y, v);
    }
    void modify(int p, int l, int r, int x, const Info &v) {
        if(r - l == 1) {
            info[p] = v;
            return;
        }
        int m = (l + r) / 2;
        push(p);
        if(x < m) {
            modify(2 * p, l, m, x, v);
        } else {
            modify(2 * p + 1, m, r, x, v);
        }
        pull(p);
    }
    void modify(int x, const Info &v) {
        modify(1, 0, n, x, v);
    }
};