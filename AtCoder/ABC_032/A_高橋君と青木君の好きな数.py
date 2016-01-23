a = int(input())
b = int(input())
n = int(input())

def gcd(a, b):
    while b:
        a, b = b, a%b
    return a

def lcm(a, b):
    return a * b // gcd(a, b)

x  = lcm(a, b)
x0 = lcm(a, b)

while x < n:
    x = x + x0

print(x)

