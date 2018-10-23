N = int(input())
data = sorted([list(map(int, input().split())) for _ in range(N)], key=lambda x: x[2])

lx, ly, lh = data[-1]

for cy in range(101):
    for cx in range(101):
        H = lh + abs(cx - lx) + abs(cy - ly)

        if all(h == max(H - abs(cx - x) - abs(cy - y), 0) for x, y, h in data):
            print(cx, cy, H)
            exit()
