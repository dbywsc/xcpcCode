#include <bits/stdc++.h>
#define endl '\n'
#define int long long
using namespace std;
const int N = 1e7;
int factinv[N];
int inv[N];
signed main(void) {
    int n, p;
    scanf("%lld%lld", &n, &p); 
    factinv[1] = inv[1] = 1;
    cout << 1 << endl;
    for(int i = 2; i <= n; i++) {
        inv[i] = 1 * (p - p / i) * inv[p % i] % p;
        cout << inv[i] << endl;
    }
    return 0;
}
