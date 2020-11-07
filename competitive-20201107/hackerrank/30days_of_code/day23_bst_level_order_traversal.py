import sys

class Node(object):
    def __init__(self, data):
        self.right = self.left = None
        self.data = data

class Solution(object):
    def insert(self, root, data):
        if root is None:
            return Node(data)
        else:
            if data <= root.data:
                cur = self.insert(root.left, data)
                root.left = cur
            else:
                cur = self.insert(root.right, data)
                root.right = cur

        return root

    def levelOrder(self, root):
        q = [root]
        v = []

        while len(q) > 0:
            p = q.pop(0)
            v.append(str(p.data))

            if p.left is not None:
                q.append(p.left)

            if p.right is not None:
                q.append(p.right)

        print(' '.join(v))


T = int(input())

myTree = Solution()
root = None

for i in range(T):
    data = int(input())
    root = myTree.insert(root, data)

myTree.levelOrder(root)
