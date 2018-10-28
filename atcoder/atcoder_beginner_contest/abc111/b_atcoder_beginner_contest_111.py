N = input()

if int(N) <= int(''.join([N[0] for _ in range(3)])):
    print(int(''.join([N[0] for _ in range(3)])))
else:
    print(''.join(str(int(N[0]) + 1) for _ in range(3)))
