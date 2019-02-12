class Solution:
    def reverse(self, x: 'int') -> 'int':
        if x < 0:
            answer = int('-' + str(x)[::-1][:-1])
        else:
            answer = int(str(x)[::-1])

        if -2 ** 31 <= answer <= 2 ** 31 + 1:
            return answer

        return 0


solution = Solution()
print(solution.reverse(123))
print(solution.reverse(-123))
print(solution.reverse(120))
