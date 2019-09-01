void build(int v, int tl, int tr) {
    if (tl == tr) {
        t[v] = a[tl];
    } else {
        int tm = (tr + tl) / 2, u = 2 * v;
        build(u, tl, tm);
        build(u + 1, tm + 1, tr);
        t[v] = t[u] + t[u + 1];
    }
}

int query(int v, int tl, int tr, int l, int r) {
    if (tl > r or tr < l) {
        return 0;
    }
    if (l <= tl and r >= tr) {
        return t[v];
    }
    int tm = (tl + tr) / 2, u = 2 * v;
    return query(u, tl, tm, l, r) + query(u + 1, tm + 1, tr, l, r);
}

void update(int v, int tl, int tr, int pos, int val) {
    if (tl == tr) {
        t[v] = val;
    } else {
        int tm = (tl + tr) / 2, u = 2 * v;
        if (pos > tm) {
            update(u + 1, tm + 1, tr, pos, val);
        } else {
            update(u, tl, tm, pos, val);
        }
        t[v] = t[u] + t[u + 1];
    }
}
