template <typename Meta, typename Comp>
struct SparseTable {
    Comp comp;
    std::vector<Meta> data[20];

    SparseTable() = default;
    SparseTable(const Comp &c): comp(c) {}

    static int lg(int x) {
        return 31 - __builtin_clz(x);
    }
    template <typename Call>
    void build(int n, Call && call) {
        for(int i = 0; i <= lg(n); i++) 
            data[i].assign(n - (1 << i) + 2, Meta{});
        for(int i = 1; i <= n; i++) data[0][i] = call(i);
        for(int k = 1; k <= lg(n); k++) {
            for(int i = 1; i + (1 << k) - 1 <= n; i++) {
                data[k][i] = comp(data[k - 1][i], data[k - 1][i + (1 << (k - 1))]);
            }
        }
    }
    Meta ask(int l, int r) {
        int k = lg(r - l + 1);
        return comp(data[k][l], data[k][r - (1 << k) + 1]);
    }
};

    auto max = [&](int x, int y) -> int {
        return x > y ? x : y;
    };
    SparseTable<int, decltype(max)> st(max);
    st.build(n, [&](int i){return a[i];});
