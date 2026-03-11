void build(std::vector<int> a, int n) {
    std::vector<int> ls(n + 1), rs(n + 1);
    std::vector<int> stk(n + 1);
    int top = 0;
    for (int i = 1; i <= n; i++) {
        int k = top;
        while (k > 0 && a[stk[k]] > a[i]) k--;
        if (k) rs[stk[k]] = i;
        if (k < top) ls[i] = stk[k + 1];
        stk[++k] = i;
        top = k;
    }
}
