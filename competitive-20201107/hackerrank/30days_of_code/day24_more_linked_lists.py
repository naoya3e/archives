class Node(object):
    def __init__(self, data):
        self.data = data
        self.next = None

class Solution(object):
    def insert(self, head, data):
            p = Node(data)
            if head is None:
                head = p
            elif head.next == None:
                head.next = p
            else:
                start = head
                while start.next != None:
                    start = start.next
                start.next = p

            return head

    def display(self, head):
        current = head
        while current:
            print(current.data, end=' ')
            current = current.next

    def removeDuplicates(self, head):
        exs = set([head.data])
        current = head

        while current.next:
            if current.next.data not in exs:
                exs.add(current.next.data)
                current = current.next
            else:
                current.next = current.next.next

        return head


T = int(input())

mylist = Solution()
head = None

for i in range(T):
    data = int(input())
    head = mylist.insert(head, data)

head = mylist.removeDuplicates(head)
mylist.display(head);
print()
