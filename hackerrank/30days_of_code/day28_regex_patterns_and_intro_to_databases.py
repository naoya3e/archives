N = int(input())
data = []

for _ in range(N):
    name, email = input().split()

    if '@gmail.com' not in email:
        continue

    data.append((name, email))

for name, email in sorted(data):
    print(name)
