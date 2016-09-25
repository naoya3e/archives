from collections import deque

players = {}
players["A"] = deque(input())
players["B"] = deque(input())
players["C"] = deque(input())

phase = "A"

while True:
    next = players[phase].popleft()
    phase = next.upper()
    if (len(players[phase]) == 0):
        print(phase)
        break
