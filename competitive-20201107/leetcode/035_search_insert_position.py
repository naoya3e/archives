class Solution:
    def searchInsert(self, nums: 'List[int]', target: 'int') -> 'int':
        for i in range(len(nums)):
            if nums[i] >= target:
                return i

        return i+1


solution = Solution()
print(2, solution.searchInsert([1,3,5,6], 5))
print(1, solution.searchInsert([1,3,5,6], 2))
print(4, solution.searchInsert([1,3,5,6], 7))
print(0, solution.searchInsert([1,3,5,6], 0))
print(3, solution.searchInsert([1,3,5,6], 6))
print(0, solution.searchInsert([1], 0))
