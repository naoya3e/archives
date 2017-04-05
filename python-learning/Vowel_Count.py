# https://www.codewars.com/kata/vowel-count

import re

def getCount(inputStr):
    return len(re.findall('[aiueo]', inputStr))

test = getCount('abracadabra')
print(test)
