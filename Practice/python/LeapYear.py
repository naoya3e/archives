# coding: utf-8

print("閏年かどうかを判定します：", end="")
year = int(input())

if (year%4 == 0 and year%100 != 0) or year%400 == 0:
    print("{}年は閏年です".format(year))
else:
    print("{}年は閏年ではありません".format(year))

