struct Data {
    int l, r, idx;
    bool operator<(Data const& oth) {
        int b1 = l / SZ, b2 = oth.l / SZ;
        if (b1 == b2) {
            return ((b1 & 1) ? r > oth.r : r < oth.r);
        }
        return b1 < b2;
    }
};

int n, a[N];
ll cur, ans[N];
vector<Data> Queries;

void insert(int x) {
    cur += cnt[x ^ k];
    ++cnt[x];
}

void remove(int x) {
    --cnt[x];
    cur -= cnt[x ^ k];
}

void Mo() {
    sort(Queries.begin(), Queries.end());
    int L = 1, R = 0;
    for (int i = 0; i < Queries.size(); ++i) {
        while (L < Queries[i].l) {
            remove(a[L++]);
        }
        while (L > Queries[i].l) {
            insert(a[--L]);
        }
        while (R < Queries[i].r) {
            insert(a[++R]);
        }
        while (R > Queries[i].r) {
            remove(a[R--]);
        }
        ans[Queries[i].idx] = cur;
    }
}
