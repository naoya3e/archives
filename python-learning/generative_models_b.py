import argparse
import numpy as np

from scipy import stats
from scipy.stats import dirichlet

parser = argparse.ArgumentParser(description='Generative model B')
parser.add_argument('-n', type=int, required=True)
args = parser.parse_args()

alpha = [1, 3, 8, 2, 6, 2]

def normalize(xs):
    return [float(i)/sum(xs) for i in xs]

def categorical(theta, n=1):
    custm = stats.rv_discrete(name='custm', values=(np.arange(len(theta)), theta))
    return custm.rvs(size=n)

theta = dirichlet.rvs(alpha).tolist()[0]
z = categorical(theta, args.n)
x = categorical(normalize(z))[0]

print('alpha     : ', alpha)
print('theta     : ', theta)
print('z         : ', z)
print('normalized: ', normalize(z))
print('x         : ', x)
