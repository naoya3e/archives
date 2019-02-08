class Solution:
    def maxProfit(self, prices):
        maxProfit, minPrice = 0, float('inf')

        for price in prices:
            minPrice = min(minPrice, price)
            profit = price - minPrice
            maxProfit = max(maxProfit, profit)

        return maxProfit


solution = Solution()

print(solution.maxProfit([7,1,5,3,6,4]))
print(solution.maxProfit([7,6,4,3,1]))
