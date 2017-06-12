from scipy.stats import dirichlet
from scipy import stats

import numpy as np

alpha = [1, 3, 8, 2, 6, 2]
l = len(alpha)

def normalize(xs):
    return [float(i)/sum(xs) for i in xs]

def categorical(l, theta):
    custm = stats.rv_discrete(name='custm', values=(np.arange(l), theta))
    return custm.rvs(size=l)

theta = dirichlet.rvs(alpha).tolist()[0]
z = categorical(l, theta)
x = categorical(l, normalize(z))

print('alpha: ', alpha)
print('theta: ', theta)
print('z    : ', z)
print('x    : ', x)
