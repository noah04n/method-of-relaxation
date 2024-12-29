#include <stdio.h>
#include <stdlib.h>
#include <string.h>


double getNeighborsSum(int row, int col, int cols, double *grid)
{
	double sum = 0;
	sum += grid[(row-1)*cols + col-1];
	sum += grid[(row-1)*cols + col];
	sum += grid[(row-1)*cols + col+1];

	sum += grid[row*cols + col-1];

	sum += grid[row*cols + col+1];

	sum += grid[(row+1)*cols + col-1];
	sum += grid[(row+1)*cols + col];
	sum += grid[(row+1)*cols + col+1];

	return sum;
}

void sweep(double *inputGrid, int rows, int cols, int precision, int proportion)
{
	// Copy the original array
	double *copy = malloc(sizeof(double) * rows * cols);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			copy[i*cols + j] = inputGrid[i*cols + j];
		}
	}
	for (int i = 1; i < (precision-1); i++)
	{
		for (int j = 1; j < (precision-1); j++)
		{
			if (!( (proportion <= i && i <= proportion*2) && (proportion <= j && j <= proportion*2)))
			{
				double sum = getNeighborsSum(i, j, cols, copy);
				inputGrid[i*cols + j] = sum/8;
			}
		}
	}
	free(copy);
}


int main(int argc, char* argv[]) {
	if (argc != 6)
	{
		fprintf(stderr, "%s", "Error: Incorrect number of inputs");
		return 1;
	}

	int rows = strtol(argv[1], NULL, 10);
	int cols = strtol(argv[2], NULL, 10);

	int precision = strtol(argv[3], NULL, 10);
	int proportion = strtol(argv[4], NULL, 10);

	int iterations = strtol(argv[5], NULL, 10);

	FILE *data = fopen("output.csv", "r");
	if (data == NULL)
	{
		perror("Error opening file\n");
		return 1;
	}

	double *grid = malloc(sizeof(double) * rows * cols);

	printf("Reading into memory from file\n");
	char line[1024];
	int row = 0;
	while (fgets(line, 1024, data))
	{
		int col = 0;
		char *token = strtok(line, ",");
		while (token != NULL)
		{
			grid[row*cols + col] = strtod(token, NULL);
			token = strtok(NULL, ",");
			col++;
		}
		row++;
	}
	fclose(data);

	printf("Beginning sweep\n");
	for (int i = 0; i < iterations; i++)
	{
		sweep(grid, rows, cols, precision, proportion);
	}

	printf("Writing to file\n");
	data = fopen("output.csv", "w");
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			fprintf(data, "%lf ", grid[i*cols + j]);
			if (j < cols - 1)
			{
				fprintf(data, ",");
			}
		}
		fprintf(data, "\n");
	}
	fclose(data);
	printf("Done\n");

	free(grid);
	return 0;
}
