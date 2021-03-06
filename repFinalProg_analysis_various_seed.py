# https://stats.biopapyrus.jp/python/plot.html を参考にした

import matplotlib.pyplot as plt
import seaborn as sns
import numpy as np
import pandas as pd

plt.style.use('default')
sns.set()  # seabornのデフォルトスタイル
sns.set_style('whitegrid')  # 背景白、グリットあり。
sns.set_palette('Set1')  # 9色

# データ生成

list_seed = [i for i in range(1,101)]

M_10_probability = [80.00, 90.00, 70.00, 70.00, 90.00, 90.00, 90.00, 90.00, 
                    80.00, 90.00, 90.00, 100.00, 80.00, 90.00, 100.00, 100.00, 
                    100.00, 90.00, 100.00, 100.00, 100.00, 100.00, 100.00, 100.00, 
                    100.00, 100.00, 100.00, 100.00, 90.00, 100.00, 100.00, 100.00, 
                    100.00, 100.00, 80.00, 100.00, 100.00, 90.00, 100.00, 90.00, 
                    100.00, 90.00, 100.00, 100.00, 100.00, 100.00, 100.00, 90.00, 
                    90.00, 100.00, 100.00, 100.00, 100.00, 100.00, 90.00, 100.00, 
                    100.00, 100.00, 100.00, 100.00, 100.00, 100.00, 100.00, 100.00, 
                    100.00, 100.00, 100.00, 100.00, 90.00, 100.00, 90.00, 100.00, 
                    100.00, 100.00, 100.00, 100.00, 100.00, 100.00, 100.00, 100.00, 
                    100.00, 100.00, 100.00, 100.00, 100.00, 100.00, 100.00, 100.00, 
                    100.00, 100.00, 100.00, 100.00, 100.00, 100.00, 100.00, 100.00, 
                    100.00, 100.00, 100.00, 100.00]

M_20_probability = [70.00, 70.00, 90.00, 85.00, 95.00, 85.00, 100.00, 95.00, 
                    100.00, 100.00, 95.00, 95.00, 100.00, 95.00, 100.00, 100.00, 
                    100.00, 95.00, 100.00, 100.00, 100.00, 100.00, 100.00, 100.00, 
                    95.00, 100.00, 100.00, 100.00, 95.00, 100.00, 100.00, 100.00, 
                    100.00, 100.00, 100.00, 100.00, 100.00, 100.00, 100.00, 100.00, 
                    100.00, 100.00, 100.00, 100.00, 100.00, 100.00, 95.00, 100.00, 
                    100.00, 95.00, 100.00, 100.00, 100.00, 100.00, 100.00, 100.00, 
                    100.00, 100.00, 100.00, 100.00, 100.00, 100.00, 100.00, 100.00, 
                    90.00, 100.00, 100.00, 100.00, 95.00, 100.00, 100.00, 100.00, 
                    100.00, 100.00, 100.00, 100.00, 100.00, 100.00, 100.00, 95.00, 
                    100.00, 100.00, 100.00, 100.00, 100.00, 100.00, 95.00, 100.00, 
                    100.00, 100.00, 100.00, 100.00, 100.00, 100.00, 100.00, 100.00, 
                    100.00, 100.00, 100.00, 100.00]

M_30_probability = [93.33, 73.33, 96.67, 96.67, 93.33, 83.33, 90.00, 96.67, 
                    86.67, 96.67, 93.33, 100.00, 96.67, 96.67, 100.00, 93.33, 
                    100.00, 100.00, 96.67, 100.00, 96.67, 96.67, 100.00, 100.00, 
                    93.33, 100.00, 100.00, 96.67, 96.67, 96.67, 100.00, 100.00, 
                    96.67, 100.00, 100.00, 100.00, 100.00, 96.67, 100.00, 100.00, 
                    100.00, 96.67, 100.00, 93.33, 100.00, 100.00, 100.00, 100.00, 
                    96.67, 96.67, 100.00, 100.00, 100.00, 100.00, 96.67, 100.00, 
                    100.00, 100.00, 96.67, 100.00, 100.00, 100.00, 100.00, 100.00, 
                    93.33, 96.67, 100.00, 100.00, 93.33, 100.00, 100.00, 100.00, 
                    96.67, 100.00, 100.00, 100.00, 100.00, 100.00, 100.00, 96.67, 
                    93.33, 100.00, 100.00, 100.00, 100.00, 100.00, 100.00, 100.00, 
                    100.00, 100.00, 100.00, 100.00, 100.00, 100.00, 96.67, 100.00, 
                    100.00, 100.00, 100.00, 100.00]


average_probability = [ (M_10_probability[i] + M_20_probability[i] + M_30_probability[i])/3 for i in range(100)]

x = np.array(list_seed)  # シード値

M_10 = np.array(M_10_probability)

M_20 = np.array(M_20_probability)

M_30 = np.array(M_30_probability)

M_ave = np.array(average_probability)

# Seriesを辞書で繋げる.キーがカラム名になる.
df = pd.DataFrame({
    'x': x,
    'M=10': M_10,
    'M=20': M_20,
    'M=30': M_30,
    "M=ave":M_ave
})

fig = plt.figure()
ax = fig.add_subplot(1, 1, 1)

# ax.plotで折れ線グラフ
ax.plot('x', 'M=10', data=df, label='M= 10',
        marker='o', linewidth=1, markersize=2.0)
ax.plot('x', 'M=20', data=df, label='M= 20',
        marker='o', linewidth=1, markersize=2.0)
ax.plot('x', 'M=30', data=df, label='M= 30',
        marker='o', linewidth=1, markersize=2.0)
ax.plot('x', 'M=ave', data=df, label='M= ave',
        marker='o', linewidth=1, markersize=3.0)

ax.legend()
ax.set_xlabel("Seed")  # 軸ラベル
ax.set_ylabel("The probability of homing success")  # 軸ラベル
ax.set_ylim(0, 100)  # y軸
plt.show()  # 描画
