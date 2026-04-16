struct Combination {
    std::vector<i64> fact, invfact;
    Combination(int n) : fact(n + 1), invfact(n + 1) {
        fact[0] = 1;
        for (int i = 1; i <= n; i++) {
            fact[i] = fact[i - 1] * i % P;
        }
        invfact[n] = qpow(fact[n], P - 2);
        for (int i = n - 1; i >= 0; i--) {
            invfact[i] = invfact[i + 1] * (i + 1) % P;
        }
    }
    i64 operator()(i64 n, i64 k) {
        if (k < 0 || k > n || n < 0) return 0;
        return fact[n] * invfact[k] % P * invfact[n - k] % P;
    }
};
