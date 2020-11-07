def hourglassSum(arr):
    s = []

    for y in range(len(arr) - 2):
        for x in range(len(arr[y]) - 2):
            up = arr[y][x] + arr[y][x+1] + arr[y][x+2]
            down = arr[y+2][x] + arr[y+2][x+1] + arr[y+2][x+2]
            s.append(up + arr[y+1][x+1] + down)

    return max(s)


matrix = []

for _ in range(6):
    matrix.append(list(map(int, input().split())))

print(hourglassSum(matrix))
