#include <iostream>
#include <vector>
using namespace std;
#define MAX 100

void input(int (*matrix)[MAX], int n, int m)
{
	for(int i=0; i<n; i++)
	{
		for(int j=0; j<m; j++)
			cin >> matrix[i][j];
	}
}

int *spiralMatrix(int (*matrix)[MAX], int r, int c)
{
	int *result = new int[r*c];
	int h1, h2, c1, c2, run;

	h1 = 0; 
	h2 = r-1;
	c1 = 0;
	c2 = c - 1;
	run = 0;

	while(h1 <= h2 && c1 <= c2)
	{
		for(int i=c1; i<=c2; i++)
			result[run++] = matrix[h1][i];
		h1++;

		for(int i=h1; i<=h2; i++)
			result[run++] = matrix[i][c2];
		c2--;

		if(h1 <= h2)
		{
			for(int i=c2; i>=c1; i--)
				result[run++] = matrix[h2][i];
			h2--;
		}

		if(c1 <= c2)
		{
			for(int i=h2; i>=h1; i--)
				result[run++] = matrix[i][c1];
			c1++;
		}
	}

	return result;
}

int main()
{
	int matrix[MAX][MAX];
	int *result = nullptr;
	int r, c;
	cin >> r >> c;

	input(matrix, r, c);
	result = spiralMatrix(matrix, r, c);

	for(int i=0; i<r*c; i++)
		cout << result[i] << " ";

	return 0;
}