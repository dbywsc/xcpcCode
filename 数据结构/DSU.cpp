struct DSU {
    std::vector<int> p, siz;
    DSU(int n): p(n + 1), siz(n + 1, 1) {
        std::iota(p.begin(), p.end(), 0);
    }
    int find(int x) {
        if(x == p[x]) return p[x];
        return p[x] = find(p[x]);
    }
    void unite(int a, int b) {
        int pa = find(a), pb = find(b);
        if(pa == pb) return;
        if(siz[pa] < siz[pb]) std::swap(pa, pb);
        p[pb] = pa;
        siz[pa] += siz[pb];
    }
    bool same(int u, int v) {return find(u) == find(v);}
    int size(int u) {return siz[find(u)];}
};
