#include <iostream>
using namespace std;

void sinh(int *a, int i, int n)
{
	for(int k=0; k<=1; k++)
	{
		a[i] = k;
		if(i == n)
		{
			for(int j=1; j<=n; j++)
				cout << a[j];
			cout << endl;
		}
		else
			sinh(a, i+1, n);
	}
}

int main()
{
	int a[100], n;
	cin >> n;
	sinh(a, 1, n);

	return 0;
}