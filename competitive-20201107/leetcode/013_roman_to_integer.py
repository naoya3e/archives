class Solution:
    def romanToInt(self, s: 'str') -> 'int':
        d = {
            'I': 1,
            'V': 5,
            'X': 10,
            'L': 50,
            'C': 100,
            'D': 500,
            'M': 1000
        }
        count = 0

        targets = [d[c] for c in s]

        for m, n in zip(targets, targets[1:] + [0]):
            if m >= n:
                count += m
            else:
                count -= m

        return count


solution = Solution()
print(3, solution.romanToInt('III'))
print(4, solution.romanToInt('IV'))
print(9, solution.romanToInt('IX'))
print(58, solution.romanToInt('LVIII'))
print(1994, solution.romanToInt('MCMXCIV'))
