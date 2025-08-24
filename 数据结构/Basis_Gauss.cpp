struct Basis {
    static const int LOG = 64;
    i64 a[LOG] {};
    bool zero;
    Basis() {
        zero = false;
    }
    void add(i64 x) {
        for(int i = LOG - 1; i >=0; i--) {
            if(x >> i & 1ll) {
                if(a[i]) {
                    x ^= a[i];
                } else {
                    a[i] = x;
                    return;
                }
            }
        }
        zero = true;
    }
    void rebuild() {
        for (int i = LOG-1; i >=0; i--) {
            for (int j = i-1; j >=0; j--) {
                if (a[i] >> j & 1) {
                    a[i] ^= a[j];
                }
            }
        }
    }
    i64 kth(i64 k) {
        if (zero) k--;
        int d = 0;
        for (int i = 0; i < LOG; i++) {
            if (a[i]) d++;
        }
        if (k >= (1LL << d)) return -1;
        i64 ans = 0;
        int cnt = 0;
        for (int i = 0; i < LOG; i++) {
            if (a[i]) {
                if (k >> cnt & 1) {
                    ans ^= a[i];
                }
                cnt++;
            }
        }
        return ans;
    }
};