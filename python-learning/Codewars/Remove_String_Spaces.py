# http://www.codewars.com/kata/remove-string-spaces

def no_space(x):
    return ''.join(x.split())

test1 = '8 j 8   mBliB8g  imjB8B8  jl  B'
print(no_space(test1))

test2 = '8 8 Bi fk8h B 8 BB8B B B  B888 c hl8 BhB fd'
print(no_space(test2))

test3 = '8aaaaa dddd r     '
print(no_space(test3))

test4 = 'jfBm  gk lf8hg  88lbe8 '
print(no_space(test4))

test5 = '8j aam'
print(no_space(test5))
