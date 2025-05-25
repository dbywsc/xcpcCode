#include <iostream>
#define int unsigned long long
using namespace std;
const int N = 1e6 + 10;
int p[N], phi[N], cnt;
bool st[N];
int get_eulers(int n) {
   phi[1] = 1;
    for(int i = 2; i <= n; i++) {
        if(!st[i]) {
            p[cnt++] = i;
            phi[i] = i - 1;
        }
        for(int j = 0; p[j] <= n / i; j++) {
            st[p[j] * i] = 1;
            if(i % p[j] == 0) {
                phi[p[j] * i] = phi[i] * p[j];
                break;
            }
            phi[p[j] * i] = phi[i] * (p[j] - 1);
        }
    }
    int res = 0;
    for(int i = 1; i <= n; i++) res += phi[i];
    return res;
}
signed main(void) {
    int n;
    cin >> n;
    cout << get_eulers(n);
    return 0;
}
