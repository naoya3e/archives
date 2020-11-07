s = input()
k = int(input())

for i in range(k):
    if not s[i] == '1':
        print(s[i])
        break
else:
    print('1')
