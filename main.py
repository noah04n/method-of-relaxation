import numpy as np
import matplotlib.pyplot as plt
import subprocess

# Adjust quality here
# Scale determines the resolution of the grid
# The number of iterations determines accuracy
scale = 30
iterations = 100000

precision = (3 * scale + 1)
grid = np.zeros((precision,precision))

proportion = (precision - 1) / 3
proportion = int(proportion)

# Set inner points to 100
for i in range(proportion, proportion*2 + 1):
    for j in range(proportion, proportion*2 + 1):
        grid[i,j] = 100

np.savetxt("output.csv", grid, delimiter=",", fmt="%d")

args = [str(precision), str(precision), str(precision), str(proportion), str(iterations)]
subprocess.run(["./sweep.out"]  + args)

grid = np.loadtxt("output.csv", delimiter=",")

plt.figure(figsize=(8,8))
plt.imshow(grid, cmap='plasma', origin='lower')
plt.colorbar(label='Electric Potential (V)')
plt.title('Electric Potential Visualization')
plt.xlabel('X')
plt.ylabel('Y')
plt.show()
