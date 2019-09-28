gp_hash_table < ll, ll > seg;

ll get(ll x) {
    return (seg.find(x) == seg.end()) ? 0 : seg[x];
}

void update(ll p, ll val) {
    for (seg[p += N] = val; p > 0; p >>= 1) {
        seg[p >> 1] = get(p) + get(p ^ 1);
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
