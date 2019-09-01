void add() {
    int n = s.size(), u = 0;
    for (int i = 0; i < n; ++i) {
        int bit = s[i] - 'a';
        if (trie[u][bit] == -1) {
            trie[u][bit] = ++val;
        }
        u = trie[u][bit];
    }
    last[u] = true;
}

bool query(int idx, int u, bool differ) {
    int n = s.size();
    if (idx == n) {
        if (differ and last[u]) {
            return true;
        }
        return false;
    }
    int bit = s[idx] - 'a';
    if (differ) {
        return query(idx + 1, trie[u][bit], differ);
    }
    bool ans = false;
    for (int i = 0; i < 3; ++i) {
        if (trie[u][i] > -1) {
            if (bit == i) {
                ans |= query(idx + 1, trie[u][i], differ);
            } else {
                ans |= query(idx + 1, trie[u][i], !differ);
            }
        }
    }
    return ans;
}
