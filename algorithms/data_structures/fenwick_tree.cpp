// 0-based
void update(int x, int y) {
    for (; x < N; x = x | (x + 1)) {
        bit[x] += y;
    }
}

ll sum(int x) {
    ll ans = 0;
    for (; x >= 0; x = (x & (x + 1)) - 1) {
        ans += bit[x];
    }
    return ans;
}

// 1-based
void update(int x, int y) {
	while (x < N) {
		bit[x] += y;
		x += x & -x;
	}
}

ll sum(int x) {
	int ans = 0;
	while(x > 0) {
		ans += bit[x];
		x -= x & -x;
	}
	return ans;
}
