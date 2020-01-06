vector < int > kasai(string s, vector < int > p) {
    int n = s.size();
    vector < int > rank(n, 0);
    for (int i = 0; i < n; ++i) {
        rank[p[i]] = i;
    }
    int k = 0;
    vector < int > lcp(n - 1, 0);
    for (int i = 0; i < n; ++i) {
        if (rank[i] == n - 1) {
            k = 0;
            continue;
        }
        int j = p[rank[i] + 1];
        while (i + k < n and j + k < n and s[i + k] == s[j + k]) {
            ++k;
        }
        lcp[rank[i]] = k;
        if (k) {
            --k;
        }
    }
    return lcp;
}
