struct Fenwick {
    int n;
    std::vector<int> a;  
    Fenwick(int n_ = 0) {
        init(n_);
    }
    void init(int n_) {
        n = n_;
        a.assign(n + 1, 0);
    }
    void add(int x, int v) {
        for (int i = x; i <= n; i += (i & -i)) {
            a[i] += v;
        }
    }
    int sum(int x) {
        int s = 0;
        for (int i = x; i > 0; i -= (i & -i)) {
            s += a[i];
        }
        return s;
    }
    int rangeSum(int l, int r) {
        return sum(r) - sum(l - 1);
    }
};
