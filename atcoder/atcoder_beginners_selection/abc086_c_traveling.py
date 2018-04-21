n = int(input())

for _ in range(n):
    t, x, y = map(int, input().split())

    if t < x + y or (x + y) % 2 != t % 2:
        print("No")
        exit()

print("Yes")
