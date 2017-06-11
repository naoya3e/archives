import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation

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

    return np.array(weight_history)


weight_history = gradient_descent(df, 0.2, 0.1)

xs = np.linspace(-0.4, 1.0, 1000)

fig = plt.figure()
ims = []

plt.plot(xs, f(xs), label='f(x)')

for weight in weight_history:
    im = plt.plot(weight, f(weight), 'ro')
    ims.append(im)

ani = animation.ArtistAnimation(fig, ims, interval=100)

plt.grid()
plt.legend()

plt.show(block=False)

c = input('Save? [y/N]')
plt.savefig('plot.png') if c == 'yes' or c == 'y' else plt.close()
