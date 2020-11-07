S = input()
print(min([abs(753 - int(S[n:n+3])) for n in range(len(S) - 2)]))
