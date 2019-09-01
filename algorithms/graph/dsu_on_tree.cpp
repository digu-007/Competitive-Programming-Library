void get_size(int s, int p) {
    sz[s] = 1;
    for (auto &x: g[s]) {
        if (x != p) {
            get_size(x, s);
            sz[s] += sz[x];
        }
    }
}

void dfs(int s, int p, int keep) {
    int mx = -1, big_child = -1;
    for (auto &x: g[s]) {
        if (x != p and sz[x] > mx) {
            mx = sz[x], big_child = x;
        }
    }
    for (auto &x: g[s]) {
        if (x != p and x != big_child) {
            dfs(x, s, 0);
        }
    }
    if (big_child != -1) {
        dfs(big_child, s, 1);
        big[big_child] = true;
    }
    dfs2(s, p, 1);
    ans[s] = sum[*cur_cnt.rbegin()]; // calculate ans here
    if (big_child != -1) {
        big[big_child] = false;
    }
    if (!keep) {
        dfs2(s, p, -1);
    }
}

void dfs2(int s, int p, int val) { // subtree function
    cur_cnt.erase(cnt[c[s]]);
    sum[cnt[c[s]]] -= c[s];
    cnt[c[s]] += val;
    cur_cnt.insert(cnt[c[s]]);
    sum[cnt[c[s]]] += c[s];
    for (auto &x: g[s]) {
        if (x != p and !big[x]) {
            dfs2(x, s, val);
        }
    }
}
