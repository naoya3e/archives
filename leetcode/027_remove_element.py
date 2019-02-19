class Solution:
    def removeElement(self, nums: 'List[int]', val: 'int') -> 'int':
        i = 0

        for j in range(len(nums)):
            if nums[j] != val:
                nums[i] = nums[j]
                i += 1

        return i


solution = Solution()
print(2, solution.removeElement([3,2,2,3], 3))
print(5, solution.removeElement([0,1,2,2,3,0,4,2], 2))
