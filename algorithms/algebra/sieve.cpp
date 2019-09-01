void sieve() {
    for (int i = 0; i < N; ++i) {
        prime[i] = true;
    }
    prime[0] = prime[1] = false;
    for (int i = 2; i * i < N; ++i) {
         if (prime[i]) {
             for (int j = i * i; j < N; j += i) {
                 prime[j] = false;
             }
        }
    }
}
