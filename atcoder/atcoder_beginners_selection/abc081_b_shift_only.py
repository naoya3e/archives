n = int(input())
a = list(map(int, input().split()))

count = 0

while True:
    odd = False

    for x in a:
        if not x % 2 == 0:
            odd = True

    if odd:
        break

    for i in range(len(a)):
        a[i] = int(a[i] / 2)

    count += 1

print(count)
