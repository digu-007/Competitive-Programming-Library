string binary(int x) {
    string ans;
    while (x) {
        if (x & 1) {
            ans += '1';
        } else {
            ans += '0';
        }
        x /= 2;
    }
    reverse(all(ans));
    return ans;
}
