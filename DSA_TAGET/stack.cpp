#include <bits/stdc++.h>
using namespace std;

void showBinaryRecur(int a, int radix)
{
	if(a / radix == 0)
		cout << a << " ";
	else
	{
		showBinaryRecur(a / radix, radix);
		cout << a % radix << " ";
	}
}

bool moveTrain(int *a, int n)
{
	stack<int> st;
	int moveCur = 1, indexCur = 0;

	while(indexCur < n)
	{
		if(a[indexCur] == moveCur)
		{
			cout << "A->C" << endl; 
			indexCur++;
			moveCur++;
		}
		else if(!st.empty() && st.top() == a[indexCur])
		{
			cout << "B->C" << endl;
			indexCur++;
			st.pop();
		}
		else if(a[indexCur] < moveCur)
			return false;
		else
		{
			cout << "A->B" << endl;
			st.push(moveCur);
			moveCur++;
		}
	}

	return true;
}

int main()
{
	int n; cin >> n;
	int *arr = new int[n];

	for(int i=0; i<n; i++)
		cin >> arr[i];


	if(moveTrain(arr, n))
		cout << "true" << endl;
	else
		cout << "false" << endl;

	return 0;
}