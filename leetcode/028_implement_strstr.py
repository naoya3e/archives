class Solution:
    def strStr(self, haystack: 'str', needle: 'str') -> 'int':
        if needle == '':
            return 0

        for i in range(len(haystack) - len(needle) + 1):
            for j in range(len(needle)):
                if haystack[i+j] != needle[j]:
                    break

                if len(needle)-1 == j:
                    return i

        return -1


solution = Solution()
print(2, solution.strStr("hello", "ll"))
print(-1, solution.strStr("aaaaa", "bba"))
print(-1, solution.strStr("heloo", "ll"))
print(4, solution.strStr("heloa", "a"))
