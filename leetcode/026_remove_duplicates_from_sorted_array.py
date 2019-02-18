class Solution:
    def removeDuplicates(self, nums: 'List[int]') -> 'int':
        if len(nums) == 0:
            return 0

        i = 0

        for j in range(1, len(nums)):
            if nums[i] != nums[j]:
                i += 1
                nums[i] = nums[j]

        return i + 1


solution = Solution()
print(2, solution.removeDuplicates([1,1,2]))
print(5, solution.removeDuplicates([0,0,1,1,1,2,2,3,3,4]))
print(0, solution.removeDuplicates([]))
