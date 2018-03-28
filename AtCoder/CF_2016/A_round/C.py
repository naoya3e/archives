s = list(input())
k = int(input())

for i in range(len(s)):
    if s[i] == "a": continue

    diff = ord("z") - ord(s[i]) + 1

    if diff <= k:
        k -= diff
        s[i] = "a"

if k > 0:
    k %= 26
    s[i] = chr(ord(s[i]) + k)

print("".join(s))
