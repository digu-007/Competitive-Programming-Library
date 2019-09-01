void dfs(int s, int par, int lvl) {
    up[s][0] = par;
    level[s] = lvl;
    sz[s] = 1;
    for (auto &x: g[s]) {
        if (x.ver != par) {
            other_end[x.idx] = x.ver;
            dfs(x.ver, s, lvl + 1);
            sz[s] += sz[x.ver];
        }
    }
}

int lca(int u, int v) {
    if (level[u] < level[v]) {
        swap(u, v);
    }
    int diff = level[u] - level[v];
    for (int j = 0; j < LG; ++j) {
        if ((diff >> j) & 1) {
            u = up[u][j];
        }
    }
    if (u == v) {
        return u;
    }
    for (int j = LG - 1; j >= 0; --j) {
        if (up[u][j] != up[v][j]) {
            u = up[u][j], v = up[v][j];
        }
    }
    return up[u][0];
}

void hld(int s, int cur, int par) {
    if (head[num] == -1) {
        head[num] = s;
    }
    chain[s] = num;
    pos[s] = ptr;
    base[ptr++] = cur;
    int special = -1, new_cost = 0;
    for (auto &x: g[s]) {
        if (x.ver != par) {
            if (special == -1 or sz[special] < sz[x.ver]) {
                special = x.ver;
                new_cost = x.cost;
            }
        }
    }
    if (special != -1) {
        hld(special, new_cost, s);
    }
    for (auto &x: g[s]) {
        if (x.ver != par and x.ver != special) {
            ++num;
            hld(x.ver, x.cost, s);
        }
    }
}

void build(int u, int l, int r) {
    if (r - l == 1) {
        t[u] = base[l];
        return;
    }
    int v = (u << 1), tm = (r + l) >> 1;
    build(v, l, tm);
    build(v | 1, tm, r);
    t[u] = max(t[v], t[v | 1]);
}

void update(int u, int l, int r, int x, int val) {
    if (l > x or r <= x) {
        return;
    }
    if (l == x and r - l == 1) {
        t[u] = val;
        return;
    }
    int v = (u << 1), tm = (r + l) >> 1;
    update(v, l, tm, x, val);
    update(v | 1, tm, r, x, val);
    t[u] = max(t[v], t[v | 1]);
}

int query_up(int u, int v) {
    if (u == v) {
        return 0;
    }
    int uchain, vchain = chain[v], ans = -1;
    while (true) {
        uchain = chain[u];
        if (uchain == vchain) {
            if (u == v) {
                break;
            }
            query(1, 0, ptr, pos[v] + 1, pos[u] + 1);
            ans = max(ans, qt[1]);
            break;
        }
        query(1, 0, ptr, pos[head[uchain]], pos[u] + 1);
        ans = max(ans, qt[1]);
        u = head[uchain];
        u = up[u][0];
    }
    return ans;
}

void query(int u, int l, int r, int tl, int tr) {
    if (l >= tr or r <= tl) {
        qt[u] = -1;
        return;
    }
    if (l >= tl and r <= tr) {
        qt[u] = t[u];
        return;
    }
    int v = (u << 1), tm = (r + l) >> 1;
    query(v, l, tm, tl, tr);
    query(v | 1, tm, r, tl, tr);
    qt[u] = max(qt[v], qt[v | 1]);
}
