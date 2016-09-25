N = int(input())
a = list(map(lambda x:x-1, list(map(int, input().split()))))

pairs = 0

for i in range(N):
    if a[a[i]] == i:
        pairs += 1

print(pairs//2)
