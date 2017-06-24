import argparse
import numpy as np
import matplotlib.pyplot as plt

from scipy import stats
from scipy.stats import norm
from sklearn.mixture import GaussianMixture

parser = argparse.ArgumentParser(description='Generative model A')
parser.add_argument('-n', type=int, default=1000)
args = parser.parse_args()

def categorical(theta):
    custm = stats.rv_discrete(name='custm', values=(np.arange(len(theta)), theta))
    return custm.rvs()


def normal(loc, scale):
    return norm.rvs(loc=loc, scale=scale)


def create_sample(n, theta, mu, si):
    x = []

    for i in range(n):
        z = categorical(theta)
        x = np.append(x, normal(mu[z], si[z]))

    return x


if __name__ == '__main__':
    # True parameters
    theta = np.array([0.6, 0.4])  # カテゴリ分布のパラメータ
    k = len(theta)

    # Generative parameters
    mu_star = np.array([0, 4])      # 平均
    si_star = np.array([1, 2])      # 分散

    n = args.n  # サンプル数

    # Prepare sample
    x  = create_sample(n, theta, mu_star, si_star)
    xs = list(map(lambda x: [x], x))

    # GaussianMixtureModel estimate with EM algorithm
    gmm = GaussianMixture(n_components=k)
    gmm.fit(xs)

    # Estimated parameters
    weights     = gmm.weights_.ravel()
    means       = gmm.means_.ravel()
    covariances = gmm.covariances_.ravel()

    # Print parameters
    print('weights    : {}'.format(theta))
    print('means      : {}'.format(mu_star))
    print('covariances: {}'.format(si_star))
    print('-'*38)
    print('weights    : {}'.format(weights))
    print('means      : {}'.format(means))
    print('covariances: {}'.format(covariances))

    # Data plot
    plt.hist(x, bins=200, normed=True, alpha=0.3, label='sample')

    X = np.linspace(min(x), max(x), 300)
    f = lambda xs: np.exp(gmm.score(xs))
    Y = np.vectorize(f)(X)

    plt.plot(X, Y, label='Estimated')

    plt.title('$\mu = {} \:\:\:\:\: \sigma = {}$'.format(mu_star.tolist(), si_star.tolist()))
    plt.legend()
    plt.grid()

    plt.show(block=False)

    c = input('Save? [(y)/N]')
    plt.savefig('plot.png') if c == 'yes' or c == 'y' else plt.close()
