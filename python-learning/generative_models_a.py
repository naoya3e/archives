from scipy import stats

import numpy as np

theta = [0.1, 0.3, 0.1, 0.2, 0.2, 0.1]
l = len(theta)

def normalize(xs):
    return [float(i)/sum(xs) for i in xs]

def categorical(l, theta):
    custm = stats.rv_discrete(name='custm', values=(np.arange(l), theta))
    return custm.rvs(size=l)

z = categorical(l, theta)
x = categorical(l, normalize(z))

print('theta: ', theta)
print('z    : ', z)
print('x    : ', x)
