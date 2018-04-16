s = input()

target = ["eraser", "erase", "dreamer", "dream"]

for t in target:
    s = s.replace(t, "")

if not s:
    print("YES")
else:
    print("NO")
