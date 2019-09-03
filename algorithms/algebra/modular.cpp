namespace ModFunctions {
	inline int add(int a, int b) {
		a += b;
		if (a >= MOD) {
			a -= MOD;
		}
		return a;
	}

	inline int sub(int a, int b) {
		a -= b;
		if (a < 0) {
			a += MOD;
		}
		return a;
	}

	inline int mul(int a, int b) {
		return int((1ll * a * b) % MOD);
	}

	inline int power(int a, ll b) {
		int res = 1;
		while (b > 0) {
			if (b & 1) {
				res = mul(res, a);
			}
			a = mul(a, a);
			b >>= 1;
		}
		return res;
	}

	inline int inv(int a) {
		a %= MOD;
		if (a < 0) {
			a += MOD;
		}
		int b = MOD, u = 0, v = 1;
		while (a) {
			int t = b / a;
			b -= t * a;
			swap(a, b);
			u -= t * v;
			swap(u, v);
		}
		assert(b == 1);
		if (u < 0) {
			u += MOD;
		}
		return u;
	}
}

using namespace ModFunctions;
