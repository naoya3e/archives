N = int(input())

count = 0
p = 0

for h in map(int, input().split()):
    count += max(0, h-p)
    p = h

print(count)
