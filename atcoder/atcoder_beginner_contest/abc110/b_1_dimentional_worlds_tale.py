n, m, x, y = map(int, input().split())
xs = list(map(int, input().split()))
ys = list(map(int, input().split()))

outbreak = True

for z in range(x, y+1):
    if x < z < y and max(xs) < z and min(ys) >= z:
        outbreak = False

print('War' if outbreak else 'No War')
