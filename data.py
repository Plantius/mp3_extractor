import numpy as np
import matplotlib.pyplot as plt, random

data = np.fromfile("data.txt", dtype='int8')
framesize = np.loadtxt("header.txt", delimiter=',', dtype=int, unpack=True)
# sample = random.choices(data, k=10000)
time = np.linspace(0, (len(data)/framesize[0])*0.026, num = len(data))

plt.figure(figsize=(16, 4), dpi=100)
plt.plot(time, data)
plt.title("Sound wave")
plt.tight_layout()
plt.show()