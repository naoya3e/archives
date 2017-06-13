import numpy as np
import matplotlib.pyplot as plt

with open('faithful.txt') as f:
    data = []
    for row in f:
        data.append(float(row.split()[0]))

print(data)

xs = np.linspace(min(data), max(data), 100)

plt.plot(xs, data)
plt.show()

# プロットされた図を閉じやすくするためのコマンド
plt.show(block=False)
c = input('Save? [y/N]: ')
if c == 'yes' or c == 'y':
    plt.savefig('plot.png')
else:
    plt.close()
