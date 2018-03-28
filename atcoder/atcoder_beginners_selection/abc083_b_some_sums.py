n, a, b = map(int, input().split())

total = 0

print(sum(i for i in range(n+1) if a <= sum(map(lambda x: int(x), str(i))) <= b))
