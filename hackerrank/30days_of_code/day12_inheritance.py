class Person(object):
    def __init__(self, firstName, lastName, idNumber):
        self.firstName = firstName
        self.lastName = lastName
        self.idNumber = idNumber

    def printPerson(self):
        print("Name:", self.lastName + ",", self.firstName)
        print("ID:", self.idNumber)


# hack print() for garbage problem
print_object = print

def print(*items_to_print):
    if 'Grade: ' in items_to_print:
        items_to_print = map(str, items_to_print)

        print_object(''.join(items_to_print))
    else:
        print_object(*items_to_print)


class Student(Person):
    def __init__(self, firstName, lastName, idNumber, scores):
        super().__init__(firstName, lastName, idNumber)
        self.scores = scores

    def calculate(self):
        ave = sum(self.scores) / len(self.scores)

        if 90 <= ave <= 100:
            return 'O'
        elif 80 <= ave < 90:
            return 'E'
        elif 70 <= ave < 80:
            return 'A'
        elif 55 <= ave < 70:
            return 'P'
        elif 40 <= ave < 55:
            return 'D'
        elif ave < 40:
            return 'T'


line = input().split()

firstName = line[0]
lastName = line[1]
idNum = line[2]

numScores = int(input()) # not needed for Python
scores = list( map(int, input().split()) )

s = Student(firstName, lastName, idNum, scores)
s.printPerson()

print("Grade: ", s.calculate())
