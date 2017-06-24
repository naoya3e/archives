import argparse
import numpy as np
import scipy as sp
import matplotlib.pyplot as plt

from scipy import stats
from scipy.stats import norm

parser = argparse.ArgumentParser(description='Generative model A')
parser.add_argument('-n', '--num', type=int, default=1000)
parser.add_argument('-t', '--time', type=int, default=50)
args = parser.parse_args()


def create_sample(theta, mu, si):
    def categorical(theta):
        custm = stats.rv_discrete(name='custm', values=(np.arange(len(theta)), theta))
        return custm.rvs()

    def normal(loc, scale):
        return norm.rvs(loc=loc, scale=scale)

    X = []

    for i in range(args.num):
        z = categorical(theta)
        X = np.append(X, normal(mu[z], si[z]))

    return X


def expectation(X, K, pi, mu, si):
    gamma = np.zeros((K, X.size))

    for k in range(K):
        gamma[k, :] = pi[k] * norm.pdf(X, loc=pi[k], scale=si[k])

    gamma /= gamma.sum(axis=0)

    return gamma


def maxmization(X, K, gamma):
    N = gamma.sum(axis=1)

    pi = gamma.sum(axis=1)
    pi /= pi.sum()

    mu = np.zeros((K, ))
    for k in range(K):
        number = sp.dot(gamma[k, :], X)
        denom  = gamma[k, :].sum()
        mu[k]  =  number / denom

    si = np.zeros((K, ))
    for k in range(K):
        number = sp.dot(gamma[k, :], (X - mu[k]) ** 2)
        denom  = gamma[k, :].sum()
        si[k]  = sp.sqrt(number / denom)

    return pi, mu, si


def calculate_Q(X, K, pi, mu, si):
    total = 0.0

    for i in range(X.size):
        temp = 0.0
        for j in range(K):
            temp += pi[j] * norm.pdf(X[i], loc=mu[j], scale=si[j])
        total += np.log(temp)

    return total


if __name__ == '__main__':
    theta = np.array([0.6, 0.4]) # カテゴリ分布のパラメータ
    K = theta.size               # クラスタ数

    # Generative parameters
    mu_star = np.array([0, 4])     # 平均
    si_star = np.array([1, 2])     # 分散

    # Prepare sample
    X = create_sample(theta, mu_star, si_star)
    N = X.size

    # Initialize parameters
    pi = np.ones(K) / K
    mu = np.random.randn(K)
    si = np.random.randn(K)
    Q  = calculate_Q(X, K, pi, mu, si)
    gamma = expectation(X, K, pi, mu, si)

    # EM algorithm
    for _ in range(args.time):
        gamma = expectation(X, K, pi, mu, si)
        pi, mu, si = maxmization(X, K, gamma)
        Q = calculate_Q(X, K, pi, mu, si)

    # Print parameters
    print('weights    : {}'.format(pi_star))
    print('means      : {}'.format(mu_star))
    print('covariances: {}'.format(si_star))
    print('-'*38)
    print('weights    : {}'.format(pi))
    print('means      : {}'.format(mu))
    print('covariances: {}'.format(si))

    # Data plot
    plt.hist(X, bins=200, normed=True, alpha=0.3, label='sample')

    plt.title('$\mu = {} \:\:\:\:\: \sigma = {}$'.format(mu_star.tolist(), si_star.tolist()))
    plt.legend()
    plt.grid()

    plt.show(block=False)

    c = input('Save? [(y)/N]')
    plt.savefig('plot.png') if c == 'yes' or c == 'y' else plt.close()
