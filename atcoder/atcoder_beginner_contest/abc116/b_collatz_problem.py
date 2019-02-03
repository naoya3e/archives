s = int(input())
a = [s]
i = 1

f = lambda n: n // 2 if n % 2 == 0 else 3 * n + 1

while True:
    a.append(f(a[i-1]))
    i += 1

    if a[-1] in a[:-1]:
        break

print(i)
