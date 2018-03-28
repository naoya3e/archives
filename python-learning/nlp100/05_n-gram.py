def ngram(seq, N):
    ret = []

    for i in range(len(seq)-N+1):
        ret.append(seq[i:i+N])

    return ret

str = 'I am an NLPer'
print(ngram(str, 2))
print(ngram(str.split(), 2))
