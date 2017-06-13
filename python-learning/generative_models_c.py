import numpy as np
from scipy import stats

states = np.array([0, 1, 2])

transition_probability = np.array([
    [0.2, 0.2, 0.6],
    [0.3, 0.2, 0.5],
    [0.3, 0.6, 0.1]
])

time = 10
theta = [0.1, 0.3, 0.1, 0.2, 0.2, 0.1]
l = len(theta)

def normalize(xs):
    return [float(i)/sum(xs) for i in xs]

def categorical(l, theta):
    custm = stats.rv_discrete(name='custm', values=(np.arange(l), theta))
    return custm.rvs(size=l)

state = states[0]

for i in range(time):
    x = categorical(l, theta)

    print('Time:  ', i)
    print('State: ', state)
    print('Out:   ', x)

    state = np.random.choice(np.arange(len(transition_probability)), p=transition_probability[state])
