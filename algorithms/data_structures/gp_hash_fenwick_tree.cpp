gp_hash_table < ll, ll > bit;

ll get(ll x) {
    return (bit.find(x) == bit.end()) ? 0 : bit[x];
}
void update(ll p, ll val) {
    for (bit[p += N] = val; p > 0; p >>= 1) {
        bit[p >> 1] = get(p) + get(p ^ 1);
    }
}

ll query(ll l, ll r) {
    ll ans = 0;
    for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
        if (l & 1) {
            ans += get(l++);
        }
        if (r & 1) {
            ans += get(--r);
        }
    }
    return ans;
}
