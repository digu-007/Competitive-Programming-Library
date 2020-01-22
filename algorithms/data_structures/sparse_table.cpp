void build() {
    for (int i = 0; i < n; ++i) {
        st[0][i] = a[i];
    }
    for (int j = 1; j < LG; ++j) {
        for (int i = 0; i + (1 << j) <= n; ++i) {
            st[j][i] = min(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
        }
    }
}

int get(int L, int R) {
    int j = lg[R - L + 1];
    return min(st[j][L], st[j][R - (1 << j) + 1]);
}

lg[1] = 0;
for (int i = 2; i <= n; ++i) {
    lg[i] = lg[i / 2] + 1;
}
