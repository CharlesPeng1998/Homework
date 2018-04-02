#include <iostream>
#include <cmath>
using namespace std;

#define pi 3.14159

int main()
{
	const double d = 5.00e-3;
	const double n = 1.83e-5;
	const double s = 1.60e-3;
	const int p = 981;
	const double g = 9.794;
	const double b = 0.00823;
	const double P = 101325;

	int U;
	double t1, t2, t3, t4;

	while (cin >> U >> t1 >> t2 >> t3 >> t4)
	{
		double t = (t1 + t2 + t3 + t4) / 4;
		double r = sqrt((9 * n*s) / (2 * g*p*t));
		double q = 9 * sqrt(2)*pi*(d / U)*sqrt(1 / (p*g))*pow(sqrt((n*s) / (1 + b / (P*r)) / t), 3);

		cout << t << ' ' << q << ' ' << endl;
	}

	return 0;
}
