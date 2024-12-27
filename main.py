import numpy as np
import matplotlib.pyplot as plt

# Adjust quality here
# Scale determines the resolution of the grid
# The number of iterations determines accuracy
scale = 25
iterations = 500

precision = (3 * scale + 1)
grid = np.zeros((precision,precision))

proportion = (precision - 1) / 3
proportion = int(proportion)

# Set inner points to 100
for i in range(proportion, proportion*2 + 1):
    for j in range(proportion, proportion*2 + 1):
        grid[i,j] = 100


def getNeighbours(row, col):
    a, b, c = [row-1, col-1], [row-1, col], [row-1, col+1]
    d, e = [row, col-1], [row, col+1]
    f, g, h = [row+1, col-1], [row+1, col], [row+1, col+1]
    return np.array([a,b,c,d,e,f,g,h])

def sweep(grid):
    inputGrid = np.ndarray.copy(grid)
    for i in range(1, precision - 1):
        for j in range(1, precision - 1):
            if not (proportion <= i <= proportion * 2 and proportion <= j <= proportion * 2):
                nbr = getNeighbours(i, j)
                sum = 0
                for k in range(8):
                    sum += inputGrid[nbr[k, 0], nbr[k, 1]]
                grid[i, j] = sum/8
    return grid

for i in range(iterations):
    grid = sweep(grid)

plt.figure(figsize=(8,8))
plt.imshow(grid, cmap='plasma', origin='lower')
plt.colorbar(label='Electric Potential (V)')
plt.title('Electric Potential Visualization')
plt.xlabel('X')
plt.ylabel('Y')
plt.show()
