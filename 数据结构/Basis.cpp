struct Basis {
    static const int LOG = 64;
    i64 a[LOG];
    Basis() {
        memset(a, 0, sizeof(a));
    }
    bool add(i64 x) {
        for(int i = LOG - 1; i >= 0; i--) {
            if(!(x & (1ll << i))) continue;
            if(!a[i]) {
                a[i] = x;
                return true;
            }
            x ^= a[i];
        }
        return false;
    }
    bool query(i64 x) const {
        for(int i = LOG - 1; i >= 0; i--) {
            if((x ^ a[i]) < x) x ^= a[i];
        }
        return x == 0;
    }
    i64 getMax(void) const {
        i64 res = 0;
        for(int i = LOG - 1; i >= 0; i--) {
            res = std::max(res, res ^ a[i]);
        }
        return res;
    }
};