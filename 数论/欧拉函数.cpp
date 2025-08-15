#include <bits/stdc++.h>
using namespace std;
int calc(int a) {
    int res = a;
    for(int i = 2; i <= a / i; i++) {
        if(a % i == 0) {
            res = res / i * (i - 1);
            while(a % i == 0) a /= i;
        }
    }
    if(a > 1) res = res / a * (a - 1);
    return res;
}
int main(void) {
    int n; cin >> n;
    while(n--) {
        int a; cin >> a;
        cout << calc(a) << endl;
    }
    return 0;
}
