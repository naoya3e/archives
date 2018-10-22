N, T = map(int, input().split())
min_cost = 1001

for i in range(N):
    cost, time = map(int, input().split())

    if time <= T:
        min_cost = min(cost, min_cost)

if min_cost <= 1000:
    print(min_cost)
else:
    print('TLE')
