import math
import heapq

adjacent = [
  [0, 4, 5, 0, 2, 0, 0],
  [4, 0, 6, 4, 3, 0, 0],
  [5, 6, 0, 6, 0, 0, 10],
  [0, 4, 6, 0, 6, 2, 6],
  [2, 3, 0, 6, 0, 9, 0],
  [0, 0, 0, 2, 9, 0, 3],
  [0, 0, 10, 6, 0, 3, 0]
]


def search(adj, goal, prev):
  path = [goal]
  dest = goal

  while prev[dest] > 0:
    path.append(prev[dest])
    dest = prev[dest]

  return list(reversed(path))


def dijkstra(adj, start, goal=None):
  n = len(adj)
  dist = [math.inf for _ in range(n)]
  prev = [math.inf for _ in range(n)]

  dist[start] = 0
  Q = []
  heapq.heappush(Q, (0, start))

  while Q:
    total, src = heapq.heappop(Q)

    for dest in range(n):
      cost = adj[src][dest]

      if cost > 0 and dist[dest] > dist[src] + cost:
        dist[dest] = dist[src] + cost
        heapq.heappush(Q, (dist[dest], dest))
        prev[dest] = src

  if goal is not None:
    return search(adj, goal, prev)
  else:
    return dist


print('始点0から終点6への最短経路のパスは {}'.format(dijkstra(adjacent, 0, 6)))
print('始点0から各点への最短経路長は {}'.format(dijkstra(adjacent, 0)))
