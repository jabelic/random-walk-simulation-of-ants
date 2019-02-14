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
seed_1 = np.array([1, 2, 1, 0, 3, 4, 14, 28])#シード値1での餌にありつけた蟻の数
seed_2 = np.array([0, 0, 0, 0, 0, 0, 7, 21])#シード値2での餌にありつけた蟻の数
seed_3 = np.array([0, 0, 2, 2, 3, 6, 16, 30])#シード値3での餌にありつけた蟻の数

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
ax.set_ylabel("The amount of ants gets feed")#軸ラベル
ax.set_ylim(-2, 32)#y軸
plt.show()#描画
