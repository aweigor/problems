# Decompose factorial into its prime factors

def is_prime(n):
    if n < 2:
        return False
    for i in range(2, int(n**0.5) + 1):
        if n % i == 0:
            return False
    return True

def get_next_prime(num, max):
    num += 1
    while num <= max:
        if is_prime(num):
            return num
        num += 1
    return None

def decomp(n):
    factors = []
    p = get_next_prime(1, n)
    while p < int(n ** 0.5) + 1:
        j = p
        c = 0
        while j <= n:
            c += n // j
            j *= p
        factors.append((p, c))
        p = get_next_prime(p, n)

    while p < n // 2 + 1:
        factors.append((p, n // p))
        p = get_next_prime(p, n)

    res = ""

    for prime, cnt in factors:
        res += f"{prime}^{cnt}"
        res += " * "

    while p <= n:
        res += str(p)
        res += " * "
        p = get_next_prime(p, n)
        if p is None:
            break

    return res[:-3]

def assert_equals(actual, expected):
    if actual != expected:
        raise RuntimeError()

def expect_error(error, fun):
    try:
        fun()
    except:
        return True
    raise RuntimeError(error)

def fixed_tests():
    def basic_test_cases():
        assert_equals(decomp(5), "2^3 * 3 * 5")
        assert_equals(decomp(25), "2^22 * 3^10 * 5^6 * 7^3 * 11^2 * 13 * 17 * 19 * 23")

    basic_test_cases()

if __name__ == '__main__':
    fixed_tests()