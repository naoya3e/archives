n, m = map(int, input().split())
x = sorted(map(int, input().split()))

if n >= m:
    print(0)
else:
    d = sorted(abs(x[i] - x[i+1]) for i in range(m-1))
    print(sum(d[:m-n]))
