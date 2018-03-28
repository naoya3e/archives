s1 = 'paraparaparadise'
s2 = 'paragraph'

def ngram(seq, N):
    ret = []

    for i in range(len(seq)-N+1):
        ret.append(seq[i:i+N])

    return ret

X = set(ngram(s1, 2))
Y = set(ngram(s2, 2))

union = X | Y
intersection = X & Y
difference = X - Y

print(union)
print(intersection)
print(difference)

print('se' in X)
print('se' in Y)
