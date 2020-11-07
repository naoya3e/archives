n = int(input())
a = list(map(int, input().split()))

alice, bob = 0, 0

for i, x in enumerate(sorted(a, reverse=True)):
    if i % 2 == 0:
        alice += x
    else:
        bob += x

print(alice - bob)
