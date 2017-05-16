# https://www.codewars.com/kata/multiples-of-3-and-5

def solution(number):
    return sum([x for x in range(number) if x%3 == 0 or x%5 == 0])

test = solution(10)
print(test)
