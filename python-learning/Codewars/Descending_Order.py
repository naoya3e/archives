# https://www.codewars.com/kata/descending-order

def Descending_Order(num):
    return int(''.join(map(str, sorted([int(x) for x in list(str(num))], reverse=True))))

test1 = Descending_Order(0)
print(test1)

test2 = Descending_Order(15)
print(test2)

test3 = Descending_Order(123456789)
print(test3)
