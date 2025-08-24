//线性筛
void work(void) {
	for(int i = 2; i <= n; i++) {
		if(!st[i]) primes[cnt++] = i;
		for(int j = 0; primes[j] <= n / i; j++) {
			st[primes[j] * i] = true;
			if(i % primes[j] == 0) break;		//此时primes[j]一定是i的最小质因子
		}
	}
}

//埃氏筛
void work(void) {
	for(int i = 2; i <= n; i++) {
		if(!st[i]) {
			primes[cnt++] = i;
			for(int j = i + i; j <= n; j += i) st[j] = true;
		}
	}
}
