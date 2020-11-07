class Solution:
    def longestCommonPrefix(self, strs: 'List[str]') -> 'str':
        answer = ''

        for cs in zip(*strs):
            if len(set(cs)) == 1:
                answer += cs[0]
            else:
                break

        return answer


solution = Solution()
print(solution.longestCommonPrefix(["flower","flow","flight"]))
print(solution.longestCommonPrefix(["dog","racecar","car"]))
print(solution.longestCommonPrefix(["aca","cba"]))
