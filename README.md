# Method of Relaxation
## Background
In electrostatics Laplace’s equation describes the electric potential in empty space. One of the properties of Laplace’s equation is that any value of the electric potential in the empty space is equal to the average of the electric potential over a sphere centered around the given point. Given this fact we can find numerical solutions to Laplace’s equation by dividing the given area into a grid of a specified resolution. We apply the boundary conditions and then begin sweeping across the grid and averaging the potential of all cells within the boundaries.

## How it Works
In this repository `sweep.c` contains the code that performs the sweep calculations. The number of iterations is specified when sweep is called and it then outputs the numerical solution to a csv file. matplotlib is then used to colour code the values and display a graphical representation of the electric potential.

## Considerations
At the moment the program is hard coded with a specific initial boundary condtion, one which resembles the cross-section of a square coaxial cable in which the center has a 100 units of potential and the outer edge has 0. Given time I hope to update this project to make it more interactive i.e. a graphical interface that allows us to define the initial boundary conditions. 
