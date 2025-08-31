struct flow {
    int cnt = 1, hd[N], nxt[M * 2], to[M * 2], limit[M * 2];
    void add(int u, int v, int w) {
        nxt[++cnt] = hd[u], hd[u] = cnt, to[cnt] = v, limit[cnt] = w;
        nxt[++cnt] = hd[v], hd[v] = cnt, to[cnt] = u, limit[cnt] = 0;
    }
    int T, dis[N], cur[N];
    i64 dfs(int id, i64 res) {
        if(id == T) return res;
        i64 flow = 0;
        for(int i = cur[id]; i && res; i = nxt[i]) {
            cur[id] = i;
            int c = std::min(res, (i64)limit[i]), it = to[i];
            if(dis[id] + 1 == dis[it] && c) {
                int k = dfs(it, c);
                flow += k, res -= k, limit[i] -= k, limit[i ^ 1] += k;
            }
        }
        if(!flow) dis[id] = -1;
        return flow;
    }
    i64 maxflow(int s, int t) {
        T = t;
        i64 flow = 0;
        while(1) {
            std::queue<int> q;
            memcpy(cur, hd, sizeof(hd));
            memset(dis, 0xff, sizeof(dis));
            q.push(s), dis[s] = 0;
            while(q.size()) {
                int u = q.front();
                q.pop();
                for(int i = hd[u]; i; i = nxt[i]) {
                    if(dis[to[i]] == -1 && limit[i]) {
                        dis[to[i]] = dis[u] + 1;
                        q.push(to[i]);
                    }
                }
            }
            if(dis[t] == -1) return flow;
            flow += dfs(s, 1e18);
        }
    }
};