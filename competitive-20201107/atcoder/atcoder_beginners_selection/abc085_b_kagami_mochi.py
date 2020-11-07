n = int(input())
d = []

for _ in range(n):
    d.append(int(input()))

print(len(set(sorted(d))))
