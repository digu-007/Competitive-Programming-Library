// Complexity: O(sqrt(n)), Calculates phi(n)
int phi(int n) {
    int ans = n;
    for (int i = 2; i * i <= n; ++i) {
        if (!(n % i)) {
            while (!(n % i)) {
                n /= i;
            }
            ans -= ans / i;
        }
    }
    if (n > 1) {
        ans -= ans / n;
    }
    return ans;
}

// Complexity: O(n * log(n)), Calculates phi(1) to phi(n)
void totient(int n) {
    for (int i = 1; i <= n; ++i) {
        phi[i] = i;
    }
    for (int i = 2; i <= n; ++i) {
        if (phi[i] == i) {
            for (int j = i; j <= n; j += i) {
                phi[j] /= i;
                phi[j] *= (i - 1);
            }
        }
    }
}
