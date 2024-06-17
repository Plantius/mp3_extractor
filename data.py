import numpy as np
import matplotlib.pyplot as plt, random

data = np.fromfile("data.txt", dtype=int)
sample = random.choices(data, k=1000)

plt.figure(figsize=(9, 6), dpi=100)
plt.plot(sample)
# plt.xlim(0, 1000)
plt.show()