n = int(input())

answer = 0

for m in range(1, n+1):
    if m % 2 == 0:
        continue

    d = [1, m]

    for i in range(2, m//2 + 1):
        if m % i == 0:
            d.append(i)

    if len(d) == 8:
        answer += 1

print(answer)
