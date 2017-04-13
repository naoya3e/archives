import random

str = "I couldn't believe that I could actually understand what I was reading : the phenomenal power of the human mind ."

def shuffle(seq):
    words = seq.split()
    shuffled = []

    for word in words:
        if len(word) > 4:
            target = list(word)[1:-1]
            random.shuffle(target)
            shuffled.append(word[0] + ''.join(target) + word[-1])
        else:
            shuffled.append(word)

    return ' '.join(shuffled)

print(str)
print(shuffle(str))
