#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int main()
{
	ifstream f;
	f.open("HiDay.txt", ios::in);
	f.seekg(4, ios_base::cur);
	f.seekg(-1, ios_base::cur);

	string s;
	getline(f, s);
	cout << s << endl;

	f.close();

	return 0;
}