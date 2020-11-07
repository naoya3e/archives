n = int(input())

s = dict([input().split() for _ in range(n)])


for _ in range(n):
    name = input()

    if name in s:
        print('{}={}'.format(name, s[name]))
    else:
        print('Not found')
