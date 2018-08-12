import math


def isPrime(n):
    if n == 1:
        return False

    for p in range(2, int(math.sqrt(n)) + 1):
        if n % p == 0:
            return False

    return True


T = int(input())

for _ in range(T):
    n = int(input())
    b = isPrime(n)

    print('Prime') if b else print('Not prime')
