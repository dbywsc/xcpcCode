#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
const int N = 2e6 + 10;
deque<int> q;
int main(void) {
	int n, k; cin >> n >> k;
	vector<int> a(n + 1);
	for(int i = 1; i <= n; i++) cin >> a[i];
	for(int i = 1; i <= n; i++) {
		while(q.size() && q.front() + k <= i) q.pop_front();
		while(q.size() && a[q.back()] < a[i]) q.pop_back();
		q.push_back(i);
		if(i >= k) cout << a[q.front()] << endl;
	}
	return 0;
}
