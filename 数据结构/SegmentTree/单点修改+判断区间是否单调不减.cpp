struct SegTree {
    struct Node {
        int l, r;
        int max, min;
        bool ok;
    };
    int n;
    std::vector<Node> tree;
    SegTree(int n_): n(n_), tree(4 * n + 1) {}
    void pull(int o) {
        tree[o].max = std::max(tree[o * 2].max, tree[o * 2 + 1].max);
        tree[o].min = std::min(tree[o * 2].min, tree[o * 2 + 1].min);
        tree[o].ok = (tree[o * 2].ok && tree[o * 2 + 1].ok && tree[o * 2].max <= tree[o * 2 + 1].min);
    }
    void build(int o, int l, int r, std::vector<std::set<int>> &S) {
        tree[o].l = l, tree[o].r = r;
        if(l == r) {
            tree[o].min = *S[l].begin();
            tree[o].max = *S[l].begin();
            tree[o].ok = true;
            return;
        }
        int m = (l + r) / 2;
        build(o * 2, l, m, S);
        build(o * 2 + 1, m + 1, r, S);
        pull(o);
    }
    void build(std::vector<std::set<int>> &S) {
        build(1, 1, n, S);
    }
    void update(int o, int v) {
        tree[o].max = v;
        tree[o].min = v;
        tree[o].ok = true;
    };
    void modify(int o, int p, int v) {
        int l = tree[o].l, r = tree[o].r;
        if(l == r) {
            update(o, v);
            return;
        }
        int mid = (l + r) / 2;
        if(p <= mid) modify(o * 2, p, v);
        else modify(o * 2 + 1, p, v);
        pull(o);
    }
    void modify(int p, int v) {
        return modify(1, p, v);
    }
    bool query(void) {
        return tree[1].ok;
    }
};
