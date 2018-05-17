/*1751367 º∆2 ≈ÌΩ°¥œ*/
#include <iostream>
using namespace std;

class Cube
{
	double length;
	double width;
	double height;
	double volume;

public:
	void input();
	void get_volume();
	void show_volume();
};

void Cube::input()
{
	cin >> length >> width >> height;
}

void Cube::get_volume()
{
	volume = length * width*height;
}

void Cube::show_volume()
{
	cout << volume << endl;
}

int main()
{
	Cube cube[3];
	for (int i = 0; i < 3; i++)
	{
		cube[i].input();
		cube[i].get_volume();
		cube[i].show_volume();
	}

	return 0;
}