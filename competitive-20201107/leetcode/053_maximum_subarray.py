class Solution:
    def maxSubArray(self, nums: 'List[int]') -> 'int':
        m = min(nums)
        s = 0

        for n in nums[1:]:
            s = max(n, n + s)
            m = max(m, s)

        return m


solution = Solution()
print(6, solution.maxSubArray([-2,1,-3,4,-1,2,1,-5,4]))
print(1, solution.maxSubArray([1]))
print(3, solution.maxSubArray([1, 2]))
print(-1, solution.maxSubArray([-1, -2]))
