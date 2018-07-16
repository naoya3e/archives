mealCost = float(input())
tipPercent = int(input())
taxPercent = int(input())

tip = mealCost * tipPercent / 100
tax = mealCost * taxPercent / 100

total = round(mealCost + tip + tax)

print('The total meal cost is {} dollars.'.format(total))
