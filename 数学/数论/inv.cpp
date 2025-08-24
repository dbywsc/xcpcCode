    //连续数字逆元的线性递推
    inv[1] = 1;
    for(int i = 2; i <= n; i++) {
        inv[i] = (i64)(p - (i64)inv[p % i] * (p / i) % p);
    }

    //阶乘递推
    inv[n] = b;
    for(int i = n - 1; i; i--) {
        inv[i] = ((i64)(i + 1) * inv[i + 1]) % p;
    }
