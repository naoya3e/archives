class Difference:
    def __init__(self, a):
        self.__elements = a

    def computeDifference(self):
        s = sorted(self.__elements)
        self.maximumDifference = abs(s[0] - s[-1])


_ = input()
a = [int(e) for e in input().split(' ')]

d = Difference(a)
d.computeDifference()

print(d.maximumDifference)
