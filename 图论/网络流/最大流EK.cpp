struct flow {
    i64 fl[N], limit[M * 2];
    int cnt = 1, hd[N], nxt[M * 2], to[M * 2], fr[N];
    void add(int u, int v, int w) {
        nxt[++cnt] = hd[u], hd[u] = cnt, to[cnt] = v, limit[cnt] = w;
        nxt[++cnt] = hd[v], hd[v] = cnt, to[cnt] = u, limit[cnt] = 0;
    }
    i64 maxflow(int s, int t) {
        i64 flow = 0;
        while(true) {
            std::queue<int> q;
            memset(fl, 0xff, sizeof(fl));
            fl[s] = 1e18, q.push(s);
            while(q.size()) {
                int u = q.front(); q.pop();
                for(int i = hd[u]; i; i = nxt[i]) {
                    int it = to[i];
                    if(limit[i] && fl[it] == -1) {
                        fl[it] = std::min(limit[i], fl[u]);
                        fr[it] = i, q.push(it);
                    }
                }
            }
            if (fl[t] == -1) return flow;
            flow += fl[t];
            for(int u = t; u != s; u = to[fr[u] ^ 1]) limit[fr[u]] -= fl[t], limit[fr[u] ^ 1] += fl[t];
        }
    }
};