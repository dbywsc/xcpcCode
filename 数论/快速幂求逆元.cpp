#include <bits/stdc++.h>
#define int long long
using namespace std;
int qpow(int a, int p) {
    int res = 1;
    int b = p - 2;
    while(b) {
        if(b & 1) {
            res = (res * a) % p;
        }
        a = a * a % p;
        b >>= 1;
    }
    return res;
}
signed main(void) {
    int n; cin >> n;
    while(n--) {
        int b, p; cin >> b >> p;
        if(!(b % p)) cout << "impossible" << endl;
        else cout << qpow(b, p) << endl;
    }
    return 0;
}
