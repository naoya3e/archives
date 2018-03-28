import argparse
import numpy as np

from scipy import stats

parser = argparse.ArgumentParser(description='Generative model C')
parser.add_argument('-t', '--time', type=int, required=True)
args = parser.parse_args()

states = np.array([0, 1, 2])

transition_probability = np.array([
    [0.2, 0.2, 0.6],
    [0.3, 0.2, 0.5],
    [0.3, 0.6, 0.1]
])

theta = [0.1, 0.3, 0.1, 0.2, 0.2, 0.1]

def normalize(xs):
    return [float(i)/sum(xs) for i in xs]

def categorical(theta):
    custm = stats.rv_discrete(name='custm', values=(np.arange(len(theta)), theta))
    return custm.rvs()

state = states[0]

print('{:^7}|{:^7}|{:^7}'.format('Time', 'State', 'Out'))
print('-'*21)

for i in range(args.time):
    x = categorical(theta)

    print('{:^7}|{:^7}|{:^7}'.format(i, state, x))

    state = np.random.choice(states, p=transition_probability[state])
