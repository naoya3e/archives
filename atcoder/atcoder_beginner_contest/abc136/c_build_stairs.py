n = int(input())
hs = list(map(int, input().split()))

c = hs[0]

for h in hs:
    if c <= h:
        c = h
    elif h + 1 == c:
        c = h + 1
    else:
        print('No')
        exit()

print('Yes')
