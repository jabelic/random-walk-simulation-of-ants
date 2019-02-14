#https://stats.biopapyrus.jp/python/plot.html を参考にした

import matplotlib.pyplot as plt
import seaborn as sns
import numpy as np
import pandas as pd

plt.style.use('default')
sns.set()#seabornのデフォルトスタイル
sns.set_style('whitegrid')#背景白、グリットあり。
sns.set_palette('Set1')#9色

#データ生成
x = np.array([10, 20, 30, 50, 100, 200, 500, 1000])
seed_1 = np.array([80.0, 70.0, 93.33333, 94.0, 93.0, 96.0, 98.8, 98.6])#シード値1
seed_2 = np.array([40.0, 45.0, 63.33333, 98.0, 95.0, 96.5, 98.4, 98.3])#シード値2
seed_3 = np.array([70.0, 90.0, 96.66667, 78.0, 96.0, 95.0, 99.0, 98.7])#シード値3

#Serieswo辞書で繋げる.キーがカラム名になる.
df = pd.DataFrame({
    'x': x,
    'seed1': seed_1,
    'seed2': seed_2,
    'seed3': seed_3
})

fig = plt.figure()
ax = fig.add_subplot(1, 1, 1)

#ax.plotで折れ線グラフ
ax.plot('x', 'seed1', data=df, label='seed 1', marker='o', linewidth=1, markersize=3.0)
ax.plot('x', 'seed2', data=df, label='seed 2', marker='o', linewidth=1, markersize=3.0)
ax.plot('x', 'seed3', data=df, label='seed 3', marker='o', linewidth=1, markersize=3.0)

ax.legend()
ax.set_xlabel("The amount of ants")#軸ラベル
ax.set_ylabel("The probability of homing success")#軸ラベル
ax.set_ylim(0, 100)#y軸
plt.show()#描画
