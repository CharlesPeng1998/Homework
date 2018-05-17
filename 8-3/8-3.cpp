/*1751367 º∆2 ≈ÌΩ°¥œ*/
#include <iostream>
using namespace std;

class Time
{
	int hour;
	int minute;
	int sec;
public:
	void set_time();
	void show_time();
	
};

int main()
{
	Time t1;
	t1.set_time();
	t1.show_time();
	return 0;
}

void Time::set_time()
{
	cin >> hour;
	cin >> minute;
	cin >> sec;
}

void Time::show_time()
{
	cout << hour << ":" << minute << ":" << sec << endl;
}
