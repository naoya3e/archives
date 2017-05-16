# https://www.codewars.com/kata/highest-and-lowest

def high_and_low(numbers):
    splitted = list(map(int, numbers.split()))
    return str(max(splited)) + ' ' + str(min(splited))

test1 = high_and_low("4 5 29 54 4 0 -214 542 -64 1 -3 6 -6")
print(test1)

test2 = high_and_low("1 -1")
print(test2)

test3 = high_and_low("1 1")
print(test3)

test4 = high_and_low("-1 -1")
print(test4)

test5 = high_and_low("1 -1 0")
print(test5)

test6 = high_and_low("1 1 0")
print(test6)

test7 = high_and_low("-1 -1 0")
print(test7)

test8 = high_and_low("42")
print(test8)
