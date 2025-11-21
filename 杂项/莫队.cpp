struct Query {
    int l, r, idx;
};

void solve(void) {
    int n, m, k; std::cin >> n >> m >> k;
    std::vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) std::cin >> a[i];
    int blen = std::sqrt(n);
    int bnum = (n + blen - 1) / blen;
    std::vector<int> bi(n + 1);
    for(int i = 1; i <= n; i++) bi[i] = (i - 1) / blen + 1;
    
    std::vector<Query> q(m + 1);
    for(int i = 1; i <= m; i++) {
        std::cin >> q[i].l >> q[i].r;
        q[i].idx = i;
    }
    std::sort(q.begin() + 1, q.end(), [&](Query x, Query y) {
        if(bi[x.l] != bi[y.l])  return bi[x.l] < bi[y.l];
        if(bi[x.l] & 1) return x.r < y.r;
        return x.r > y.r;
    });
    

    std::vector<int> cnt(k + 1);
    std::vector<int> ans(n + 1);
    i64 sum = 0;

    auto add = [&](int v) -> void {
        sum -= cnt[v] * cnt[v];
        ++cnt[v];
        sum += cnt[v] * cnt[v];
    };

    auto del = [&](int v) -> void {
        sum -= cnt[v] * cnt[v];
        --cnt[v];
        sum += cnt[v] * cnt[v];
    };

    int winl = 1, winr = 0;
    for(int i = 1; i <= m; i++) {
        int jobl = q[i].l, jobr = q[i].r;
        while(winl > jobl) {
            add(a[--winl]);
        }
        while(winr < jobr) {
            add(a[++winr]);
        }
        while(winl < jobl) {
            del(a[winl++]);
        }
        while(winr > jobr) {
            del(a[winr--]);
        }
        ans[q[i].idx] = sum;
    }

    for(int i = 1; i <= m; i++) std::cout << ans[i] << '\n';
}
