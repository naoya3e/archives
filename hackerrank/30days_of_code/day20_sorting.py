def sort(a, n):
    n_swaps = 0

    for i in range(n):
        for j in range(n-1):
            if a[j] > a[j+1]:
                a[j], a[j+1] = a[j+1], a[j]
                n_swaps += 1

    return a, n_swaps


n = int(input())
a = list(map(int, input().split()))

s, n_swaps = sort(a, n)

print('Array is sorted in {} swaps.'.format(n_swaps))
print('First Element: {}'.format(s[0]))
print('Last Element: {}'.format(s[-1]))
