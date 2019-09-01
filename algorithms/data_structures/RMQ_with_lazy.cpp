void push(int v) {
    int u = 2 * v;
    t[u] += lazy[v];
    lazy[u] += lazy[v];
    t[u + 1] += lazy[v];
    lazy[u + 1] += lazy[v];
    lazy[v] = 0;
}

void build(int v, int tl, int tr) {
    if (tl == tr) {
        t[v] = a[tl];
    } else {
        int tm = (tr + tl) / 2, u = 2 * v;
        build(u, tl, tm);
        build(u + 1, tm + 1, tr);
        t[v] = min(t[u], t[u + 1]);
    }
}

ll query(int v, int tl, int tr, int l, int r) {
    if (tl > r or tr < l) {
        return LINF;
    }
    if (l <= tl and r >= tr) {
        return t[v];
    }
    push(v);
    int tm = (tl + tr) / 2, u = 2 * v;
    return min(query(u, tl, tm, l, r), query(u + 1, tm + 1, tr, l, r));
}

void update(int v, int tl, int tr, int l, int r, ll val) {
    if (l > r) {
        return;
    }
    if (tl == l and tr == r) {
        t[v] += val;
        lazy[v] += val;
    } else {
        push(v);
        int tm = (tl + tr) / 2, u = 2 * v;
        update(u, tl, tm, l, min(r, tm) ,val);
        update(u + 1, tm + 1, tr, max(l, tm + 1), r, val);
        t[v] = min(t[u], t[u + 1]);
    }
}
