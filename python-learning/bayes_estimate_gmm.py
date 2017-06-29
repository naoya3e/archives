import argparse
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation

from scipy.stats import norm


# コマンドライン引数
parser = argparse.ArgumentParser(description='ベイズ推定による正規分布の平均を学習')
parser.add_argument('-v', '--var', type=float, default=1.0)
parser.add_argument('-m', '--mean', type=float, default=2.0)
args = parser.parse_args()


# 観測データ生成
N = 1000
sample = norm.rvs(args.mean, args.var, size=N)

# 正規分布の分散は既知だとする
fixed_var = args.var

# アニメーションプロット準備
fig = plt.figure()
ims = []
xs = np.linspace(-2, 4, 10000)

# ベイズ推定によって観測データのモデルである正規分布の平均を学習する
m_0 = 0.0
v_0 = fixed_var

for i, n in enumerate([2, 4, 10, 100, 1000]):
    train_sample = sample[0:n]

    m_ML = np.mean(train_sample)
    denom = n * v_0 + fixed_var
    m_N = fixed_var / denom * m_0 + n * v_0 / denom * m_ML
    v_N = v_0 * fixed_var / (fixed_var + v_0 * n)

    im = plt.plot(xs, norm.pdf(xs, m_N, v_N), label=('Number of sample: {}'.format(n)))
    ims.append(im)

print('TRUE mean: {}   ESTIMATED mean: {}'.format(args.mean, m_N))
print('TRUE var : {}   ESTIMATED var : {}'.format(args.var, v_N))

ani = animation.ArtistAnimation(fig, ims, interval=800)

plt.ylim(-4, 30)
plt.title('Estimate mean of Gaussian distribution')
plt.legend()

plt.show(block=False)

c = input('Save? [(y)/N]')
plt.savefig('plot.png') if c == 'yes' or c == 'y' else plt.close()
