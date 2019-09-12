// #define int long long
// FFT with MOD

const int Maxb = 19;
const int Maxp = 450;

vll rev;
vector < com > omega;

void calc_rev(int n, int log_n) {
	omega.assign(n, 0);
	rev.assign(n, 0);
	for (int i = 0; i < n; ++i) {
		rev[i] = 0;
		for (int j = 0; j < log_n; ++j) {
			if ((i >> j) & 1) {
                rev[i] |= 1 << (log_n - j - 1);
            }
		}
	}
}

void fft(vector < com > &A, int n, bool invert) {
	for (int i = 0; i < n; ++i) {
		if (i < rev[i]) {
            swap(A[i], A[rev[i]]);
        }
	}
	for (int len = 2; len <= n; len <<= 1) {
		double ang = 2 * PI / len * (invert ? -1 : 1);
		int half = (len >> 1);
		com cc(cos(ang), sin(ang));
		omega[0] = com(1, 0);
		for (int i = 1; i < half; ++i) {
            omega[i] = omega[i - 1] * cc;
        }
		for (int i = 0; i < n; i += len) {
			com t;
			int pu = i, pv = i + half, pu_end = i + half, pw = 0;
			for (; pu != pu_end; ++pu, ++pv, ++pw) {
				t = A[pv] * omega[pw];
				A[pv] = A[pu] - t;
				A[pu] += t;
			}
		}
	}
	if (invert) {
        for(int i = 0; i < n; ++i) {
            A[i] /= n;
        }
    }
}

void multiply(int n, vector < com > &A, vector < com > &B, vll &C) {
	fft(A, n, false);
	fft(B, n, false);
	for (int i = 0; i < n; ++i) {
        A[i] *= B[i];
    }
	fft(A, n, true);
	for (int i = 0; i < n; ++i) {
		C[i] = (int)(A[i].real() + 0.5);
		C[i] %= MOD;
	}
}

void solve(int n, vll &coeffA, vll &coeffB, vll &result, bool big1, bool big2) { //Call 4 times: 00, 01, 10, 11
	vector < com > A(n), B(n);
	for (int i = 0; i < n; ++i)	{
		A[i] = big1 ? coeffA[i] / Maxp : coeffA[i] % Maxp;
		B[i] = 0;
	}
	for (int i = 0; i < n; ++i) {
		B[i] = big2 ? coeffB[i] / Maxp : coeffB[i] % Maxp;
	}
	vll C(n);
	multiply(n, A, B, C);
	for (int i = 0; i < n; ++i) {
		int add = C[i];
		if (big1) {
            add *= Maxp;
        }
		if (big2) {
            add *= Maxp;
        }
		add %= MOD;
		result[i] += add;
		result[i] %= MOD;
	}
}

void do_FFT(vll &A, vll &B, vll &result) {
	int n = 1, bits = 0;
	while (n < 2 * A.size() or n < 2 * B.size()) {
        n <<= 1, ++bits;
    }
	result.assign(n, 0);
	calc_rev(n, bits);
	vll tempA(A.begin(), A.end());
	vll tempB(B.begin(), B.end());
	tempA.resize(n);
	tempB.resize(n);
	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < 2; ++j) {
			solve(n, tempA, tempB, result, i, j);
		}
	}
}

--------------------------------------------------------------------------------------------------

// FFT without MOD

vll rev;
vector < com > omega;

void calc_rev(int n, int log_n) {
	omega.assign(n, 0);
	rev.assign(n, 0);
	for (int i = 0; i < n; ++i) {
		rev[i] = 0;
		for (int j = 0; j < log_n; ++j) {
			if ((i >> j) & 1) {
                rev[i] |= 1 << (log_n - j - 1);
            }
		}
	}
}

void fft(vector < com > &A, int n, bool invert) {
	for (int i = 0; i < n; ++i) {
		if (i < rev[i]) {
            swap(A[i], A[rev[i]]);
        }
	}
	for (int len = 2; len <= n; len <<= 1) {
		double ang = 2 * PI / len * (invert ? -1 : 1);
		int half = (len >> 1);
		com cc(cos(ang), sin(ang));
		omega[0] = com(1, 0);
		for (int i = 1; i < half; ++i) {
            omega[i] = omega[i - 1] * cc;
        }
		for (int i = 0; i < n; i += len) {
			com t;
			int pu = i, pv = i + half, pu_end = i + half, pw = 0;
			for (; pu != pu_end; ++pu, ++pv, ++pw) {
				t = A[pv] * omega[pw];
				A[pv] = A[pu] - t;
				A[pu] += t;
			}
		}
	}
	if (invert) {
        for(int i = 0; i < n; ++i) {
            A[i] /= n;
        }
    }
}

void multiply(int n, vector < com > &A, vector < com > &B, vll &C) {
	fft(A, n, false);
	fft(B, n, false);
	for (int i = 0; i < n; ++i) {
        A[i] *= B[i];
    }
	fft(A, n, true);
	for (int i = 0; i < n; ++i) {
		C[i] = (int)(A[i].real() + 0.5);
	}
}

void solve(int n, vll &coeffA, vll &coeffB, vll &result) {
	vector < com > A(n), B(n);
	for (int i = 0; i < n; ++i)	{
		A[i] = coeffA[i];
		B[i] = 0;
	}
	for (int i = 0; i < n; ++i) {
		B[i] = coeffB[i];
	}
	vll C(n);
	multiply(n, A, B, C);
	for (int i = 0; i < n; ++i) {
		int add = C[i];
		result[i] += add;
	}
}

void do_FFT(vll &A, vll &B, vll &result) {
	int n = 1, bits = 0;
	while (n < 2 * A.size() or n < 2 * B.size()) {
        n <<= 1, ++bits;
    }
	result.assign(n, 0);
	calc_rev(n, bits);
	vll tempA(A.begin(), A.end());
	vll tempB(B.begin(), B.end());
	tempA.resize(n);
	tempB.resize(n);
    solve(n, tempA, tempB, result);
}

// Source: https://github.com/Ashishgup1/Competitive-Coding/blob/master/FFT%20(Iterative).cpp
