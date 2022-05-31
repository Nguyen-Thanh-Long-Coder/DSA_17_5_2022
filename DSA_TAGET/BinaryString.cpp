#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
using namespace std;

int main()
{
	ifstream f;
	f.open("HiDay.txt", ios_base::in);
	string str = "Nguyen Thanh Long";
	cout << setfill('0') << setw(20) << str << endl;

	f.close();

	return 0;
}