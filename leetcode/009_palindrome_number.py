class Solution:
    def isPalindrome(self, x: 'int') -> 'bool':
        return str(x) == str(x)[::-1]


solution = Solution()
print(solution.isPalindrome(121))
print(solution.isPalindrome(-121))
print(solution.isPalindrome(10))
