N, M, src, dst = map(int, input().split())
L = []
s = [[] for i in range(M)]
w = [[] for i in range(M)]

for i in range(M):
    L.append(int(input()))
    s[i] = list(map(int, input().split()))
    w[i] = list(map(int, input().split()))



