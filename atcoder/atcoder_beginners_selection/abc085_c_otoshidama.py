n, y = map(int, input().split())

def solve():
    for i in range(n+1):
        for j in range(n-i+1):
            k = n - i - j
            total = 10000*i + 5000*j + 1000*k

            if i+j+k == n and total == y:
                return i, j, k

    return -1, -1, -1

a, b, c = solve()
print("{} {} {}".format(a, b, c))
