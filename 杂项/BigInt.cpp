struct BigInt {
    static const int DIGIT = 5000;
    int a[DIGIT];
    //提供int、i64、string构造，默认使用int构造
    BigInt(int x = 0) : a{} {
        for(int i = 0; x; i++) {
            a[i] = x % 10;
            x /= 10;
        }
    }
    /*BigInt(i64 x) : a{} {
        for(int i = 0; x; i++) {
            a[i] = (int)(x % 10);
            x /= 10;
        }
    }
    BigInt(std::string &s) : a{} {
        int n = s.size();
        for(int i = 0; i < n && i < DIGIT; i++) {
            char c = s[n - i - 1];
            if(c < '0' || c > '9') throw std::invalid_argument("BigInt(const string): 非法字符");
            a[i] = c - '0';
        }
    }*/
    BigInt &operator*=(int x) {
        for(int i = 0; i < DIGIT; i++) {
            a[i] *= x;
        }
        for(int i = 0; i < DIGIT - 1; i++) {
            a[i + 1] += a[i] / 10;
            a[i] %= 10;
        }
        return *this;
    }
    BigInt &operator/=(int x) {
        int remainder = 0;
        for (int i = DIGIT - 1; i >= 0; i--) {
            long long current = a[i] + remainder * 10LL;
            a[i] = static_cast<int>(current / x);
            remainder = static_cast<int>(current % x);
        }
        return *this;
    }
    BigInt &operator+=(const BigInt &x) {
        for(int i = 0; i < DIGIT; i++) {
            a[i] += x.a[i];
            if(a[i] >= 10) {
                a[i + 1] += 1;
                a[i] -= 10;
            }
        }
        return *this;
    }
    //满足 a > b
    BigInt& operator-=(const BigInt &b) {
        for(int i = 0; i < DIGIT; i++) {
            a[i] -= b.a[i];
            if(a[i] < 0) {
                a[i] += 10;
                a[i+1]--;
            }
        }
        return *this;
    }
};
std::ostream &operator<<(std::ostream &o, const BigInt &x) {
    int t = BigInt::DIGIT - 1;
    while (t > 0 && x.a[t] == 0) t--;
    for(int i = t; i >= 0; i--) {
        o << x.a[i];
    }
    return o;
}
std::istream &operator>>(std::istream &in, BigInt &x) {
    std::string s;
    if(!(in >> s)) return in;
    for(int i = 0; i < BigInt::DIGIT; i++) x.a[i] = 0;
    int n = s.size();
    for(int i = 0; i < n; i++) {
        char c = s[n - i - 1];
        if(c < '0' || c > '9') {
            in.setstate(std::ios::failbit);
            return in;
        }
        x.a[i] = c - '0';
    }
    return in;
}
inline BigInt operator+(BigInt a, const BigInt &b) {
    return a += b;
}
inline BigInt operator-(BigInt a, const BigInt &b) {
    return a -= b;
}

inline BigInt operator*(BigInt a, int b) {
    return a *= b;
}
inline BigInt operator/(BigInt a, int b) {
    return a /= b;
}