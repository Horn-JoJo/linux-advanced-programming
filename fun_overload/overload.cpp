#include <iostream>
using namespace std;

void add(int x, int y)
{
	cout << "res = " << x + y << endl;
}

void add(int x, int y, double z)
{
	cout << "res = " << x + y + z << endl;
}

int main()
{

	add(1, 2);
	add(1, 2, 3);
	return 0;
}
