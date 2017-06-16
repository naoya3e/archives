import argparse
import numpy as np
import matplotlib.pyplot as plt

from scipy import stats

parser = argparse.ArgumentParser(description='Generative model A')
parser.add_argument('-n', type=int, required=True)
parser.add_argument('-p', '--plot', action='store_true')
args = parser.parse_args()

theta = [0.1, 0.3, 0.1, 0.2, 0.2, 0.1]

def normalize(xs):
    return [float(i)/sum(xs) for i in xs]

def categorical(theta, n=1):
    custm = stats.rv_discrete(name='custm', values=(np.arange(len(theta)), theta))
    return custm.rvs(size=n)

z = categorical(theta, args.n)
x = categorical(normalize(z))[0]

print('theta     : ', theta)
print('z         : ', z)
print('normalized: ', normalize(z))
print('x         : ', x)

if args.plot:
    px = [categorical(normalize(z))[0] for _ in range(1000)]

    labels, counts = np.unique(px, return_counts=True)
    plt.bar(labels, counts, align='center')
    plt.gca().set_xticks(range(args.n))

    plt.title('Z = {} ({} times)'.format(z, 1000))
    plt.grid()

    plt.show(block=False)

    c = input('Save? [y/N]')
    plt.savefig('plot.png') if c == 'yes' or c == 'y' else plt.close()
