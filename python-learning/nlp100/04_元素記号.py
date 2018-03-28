str = 'Hi He Lied Because Boron Could Not Oxidize Fluorine. New Nations Might Also Sign Peace Security Clause. Arthur King Can.'

dict = {}
pick = [0, 4, 5, 6, 7, 8, 14, 15, 18]
word = str.split()

for i, w in enumerate(word):
    head = 1 if i in pick else 2
    dict[word[i][:head]] = i

print(dict)
