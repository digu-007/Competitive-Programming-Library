vector<int> seq = {a[0]};
for (int i = 1; i < n; ++i) {
    if (a[i] < seq.front()) {
        seq.front() = a[i];
    } else if (a[i] > seq.back()) {
        seq.emplace_back(a[i]);
    } else {
        int idx = lower_bound(seq.begin(), seq.end(), a[i]) - seq.begin();
        if (idx < seq.size() and seq[idx] != a[i]) seq[idx] = a[i];
    }
}
