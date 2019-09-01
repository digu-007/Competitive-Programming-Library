void prime_factorization() {
    for (int i = 2; i < N; ++i) {
        if (factors[i].empty()) {
            for (int j = i; j < N; j += i) {
                factors[j].eb(i);
            }
        }
    }
}
