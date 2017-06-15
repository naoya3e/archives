import argparse
import numpy as np

from scipy import stats

parser = argparse.ArgumentParser(description='Generative model A')
parser.add_argument('-n', type=int, required=True)
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
