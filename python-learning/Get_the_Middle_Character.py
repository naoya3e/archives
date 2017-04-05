# https://www.codewars.com/kata/get-the-middle-character

def get_middle(s):
    mid = len(s)//2

    if len(s) & 1:
        return s[mid]
    else:
        return s[mid-1] + s[mid]

test1 = get_middle("test")
print(test)

test2 = get_middle("testing")
print(test2)

test3 = get_middle("middle")
print(test3)

test4 = get_middle("A")
print(test4)

test5 = get_middle("of")
print(test5)
