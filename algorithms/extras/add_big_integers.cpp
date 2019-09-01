void solve(string a, string b) {
    while (a.size() != b.size()) {
        if (b.size() > a.size()) {
            a = '0' + a;
        } else {
            b = '0' + b;
        }
    }
    int sz = a.size(), car = 0;
    for (int i = sz - 1; i >= 0; --i) {
        int temp = a[i] + b[i] - 2 * '0' + car;
        car = temp / 10;
        ans += char(temp % 10 + '0');
    }
    if (car) {
        ans += char(car + '0');
    }
    reverse(all(ans));
}
