vector < int > z_function(string s) {
    int n = s.size();
    vector < int > z(n);
    for (int i = 1, l = 0, r = 0; i < n; ++i) {
        if (i <= r) {
            z[i] = min(r - i + 1, z[i - l]);
        }
        while (i + z[i] < n and s[z[i]] == s[z[i] + i]) {
            ++z[i];
        }
        if (z[i] + i - 1 > r) {
            l = i, r = z[i] + i - 1;
        }
    }
    return z;
}
