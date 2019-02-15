class Solution:
    def isValid(self, s: 'str') -> 'bool':
        opens =  ('(', '{', '[')
        closes = (')', '}', ']')

        stack = []

        for c in s:
            if c in opens:
                stack.append(c)

            if c in closes:
                if len(stack) == 0:
                    return False

                n = stack.pop()

                if not opens.index(n) == closes.index(c):
                    return False

        return not stack


solution = Solution()
print(True, solution.isValid('()'))
print(False, solution.isValid('(){[}'))
print(True, solution.isValid('()[]{}'))
print(False, solution.isValid('(]'))
print(False, solution.isValid('([)]'))
print(True, solution.isValid('{()}'))
print(False, solution.isValid(']'))
