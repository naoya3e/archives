import numpy as np
import matplotlib.pyplot as plt

def f(x):
    return x**4 - x**3

def df(x):
    h = 1e-4
    return (f(x+h) - f(x-h)) / (2 * h)

def gradient_descent(df, init, rate):
    eps = 1e-10
    trial = 1000

    weight = init
    weight_history = [init]

    for i in range(trial):
        weight_new = weight - rate * df(weight)

        if abs(weight - weight_new) < eps:
            break

        weight = weight_new
        weight_history.append(weight)

    return (weight, np.array(weight_history))


weight, weight_history = gradient_descent(df, 0.2, 0.1)
# weight, weight_history = gradient_descent(df, -0.3, 0.1)

xs = np.linspace(-0.4, 1.0, 1000)

plt.plot(xs, f(xs), label='f(x)')

plt.plot(weight_history, f(weight_history), 'o')

plt.grid()
plt.legend()

plt.show(block=False)

c = input('Save? [y/N]')
plt.savefig('plot.png') if c == 'yes' or c == 'y' else plt.close()
