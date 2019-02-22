class Solution:
    def countAndSay(self, n: 'int') -> 'str':
        look = '1'

        for _ in range(n-1):
            count = 1
            joined = ''

            what = look[0]
            look = look[1:] + '@'

            for c in look:
                if what == c:
                    count += 1
                else:
                    joined += str(count) + what

                    count = 1
                    what = c

            look = joined

        return look


solution = Solution()
print("1", solution.countAndSay(1))
print("11", solution.countAndSay(2))
print("21", solution.countAndSay(3))
print("1211", solution.countAndSay(4))
