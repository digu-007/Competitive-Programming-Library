void precompute(int n) {
    fact[0] = 1;
    for (int i = 1; i <= n; ++i) {
        fact[i] = mul(i, fact[i - 1]);
    }
    invfact[n] = inv(fact[n]);
    for (int i = n - 1; i >= 0; --i) {
        invfact[i] = mul(invfact[i + 1], i + 1);
    }
}

int ncr(int a, int b) {
    if (b > a) {
        return 0;
    }
    int ans = fact[a];
    ans = mul(ans, inv(mul(fact[b], fact[a - b])));
    return ans;
}
