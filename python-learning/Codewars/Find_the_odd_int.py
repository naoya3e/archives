# https://www.codewars.com/kata/find-the-odd-int

from collections import Counter

def find_it(seq):
    count = Counter(seq)
    for key, value in count.items():
        if value & 1 == 1:
            return key

test = find_it([20,1,-1,2,-2,3,3,5,5,1,2,4,20,4,-1,-2,5])
print(test)
