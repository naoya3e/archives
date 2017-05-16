# https://www.codewars.com/kata/jaden-casing-strings

def toJadenCase(string):
    return ' '.join(s.capitalize() for s in string.split())

test = toJadenCase("How can mirrors be real if our eyes aren't real")
print(test)

# return string.title()
#   これだとクォートの後ろの文字をcapitalizeしてしまうため不適
