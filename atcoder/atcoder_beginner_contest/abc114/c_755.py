N = int(input())

def dfs(s):
    if int(s) > N:
        return 0

    count = 1 if all(s.count(c) > 0 for c in '753') else 0

    for c in '753':
        count += dfs(s + c)

    return count

print(dfs('0'))
