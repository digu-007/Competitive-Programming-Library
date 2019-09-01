bool is_prime(int a) {
    if (a < 2) {
        return false;
    } else if (a == 2) {
        return true;
    }
    if (a % 2 == 0) {
        return false;
    }
    for (int i = 3; i <= sqrt(a); i += 2) {
        if (a % i == 0) {
            return false;
        }
    }
    return true;
}
