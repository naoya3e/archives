N = int(input())
K = list(map(int, input().split()))

L = [K[0]]
for i in range(N-2):
    L.append(min(K[i], K[i+1]))
L.append(K[i+1])

print(*L)

