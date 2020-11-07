def factorial(n, total=1):
    if n == 1:
        return total

    return factorial(n-1, total * n)

N = int(input())
print(factorial(N))
