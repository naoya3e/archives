s = input()
k = int(input())

start = 0
end = start+k

dict = {}

while end <= len(s):
    slice = s[start:end]
    if slice not in dict:
        dict[slice] = 1
    start += 1
    end += 1

print(len(dict))

