//必须建立静态对象并且每次init(),不然会炸
struct Trie {
    static const int M = 1e6 + 10, size = 128;
    int idx = 0;
    int son[M][size] = {0};
    int pre[M] = {0}, cnt[M] = {0};
    void init() {
        for(int i = 0; i < size; i++) son[0][i] = 0;
        memset(pre, 0, (idx + 1) * 4);
        memset(cnt, 0, (idx + 1) * 4);
        idx = 0;
    }
    bool insert(std::string s) {
        int p = 0;
        for(int i = 0; i < s.size(); i++) {
            int u = int(s[i]);
            if(u < 0 || u >= size) return false;
            if(!son[p][u]) {
                son[p][u] = ++idx;
                for(int i = 0; i < size; i++)
                    son[idx][i] = 0;
            }
            p = son[p][u];
            pre[p]++;
        }
        cnt[p]++;
        return true;
    }
    /*
        1 返回单词出现次数
        2 返回前缀出现次数
     */
    int query(std::string s, int op) {
        int p = 0;
        for(int i = 0; i < s.size(); i++) {
            int u = int(s[i]);
            if(!son[p][u]) return 0;
            p = son[p][u];
        }
        if(op == 1) return cnt[p];
        if(op == 2) return pre[p];
        return -1;
    }
};