# http://www.codewars.com/kata/sort-an-array-by-value-and-index/train/python

def sort_by_value_and_index(arr):
    co = list(range(1, len(arr)+1))
    keys = [x*y for x, y in zip(arr, co)]
    merged = list(zip(arr, keys))
    tuples = sorted(merged, key=lambda x: x[1])
    return [x[0] for x in tuples]

test1 = [1, 2, 3, 4, 5]
print(sort_by_value_and_index(test1))

test2 = [23, 2, 3, 4, 5]
print(sort_by_value_and_index(test2))
