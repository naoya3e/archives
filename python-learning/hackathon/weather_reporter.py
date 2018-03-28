import re
import argparse
import numpy as np
import matplotlib.pyplot as plt
from collections import defaultdict

parser = argparse.ArgumentParser(description="I'm a weather reporter only April in Kurashiki-shi :P")
parser.add_argument('-y', '--year', default='2016')
parser.add_argument('-f', '--filename', required=True)

args = parser.parse_args()

with open(args.filename, 'r') as f:
    # 年ごとのデータを保存するためのdictを用意
    data = defaultdict(lambda: [])

    for i, line in enumerate(f):
        # 最初の4行はカラムの説明なので読み飛ばす
        if i < 3: continue

        # CSVファイルのためカンマ区切りでリストにする
        info = line.split((','))
        # 取得したい日付/気温のカラムを指定して代入
        date, d_ave, d_max, d_min = info[0], float(info[1]), float(info[4]), float(info[7])

        # 年ごとに分けてデータをタプルのリストとして保存
        year = re.match('^\d{4}', date).group()
        data[year].append((d_ave, d_max, d_min))

if data[args.year]:
    # X軸用のデータを用意(30日)
    x = np.arange(1, 31)

    # データをNumpy Arrayにする
    target = np.array(data[args.year])
    # それぞれのカラムの平均を取得する
    month_average = [np.average(target[:, 0]), np.average(target[:, 1]), np.average(target[:, 2])]

    plt.plot(x, target[:, 0], '-', label='Ave daily', color='#43c528')
    plt.plot(x, [month_average[0] for i in range(len(x))], '--', label='Ave monthly', color='#90e57f')

    plt.plot(x, target[:, 1], '-', label='Max daily', color='#fb1548')
    plt.plot(x, [month_average[1] for i in range(len(x))], '--', label='Max monthly', color='#fd8aa3')

    plt.plot(x, target[:, 2], '-', label='Min daily', color='#3e47d1')
    plt.plot(x, [month_average[2] for i in range(len(x))], '--', label='Min monthly', color='#9ea3e8')

    plt.grid()
    plt.title('Weather infomation - {}.4'.format(args.year))
    plt.legend(loc='best')
    plt.xlabel('Day')
    plt.ylabel('Temperature [℃]')
    plt.xlim(1,30)
    plt.ylim(0,40)

    # プロットされた図を閉じやすくするためのコマンド
    plt.show(block=False)
    c = input('Save? [y/N]: ')
    if c == 'yes' or c == 'y':
        plt.savefig('plot.png')
    else:
        plt.close()

else:
    print('{}年4月のデータは存在しません...'.format(args.year))
