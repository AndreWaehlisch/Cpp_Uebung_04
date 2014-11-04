#include <iostream>
#include <cmath>
using namespace std;

const int MAXSTEPS = 100;

class MyFunc {
 public:

	double a;

	 MyFunc(double init) {
		a = init;
	} double operator() (double x) {
		return (sinh(x) / x - (a * x * x));
	}
};

int bracket(MyFunc & func, double &a, double &b)
{
	double f = func(a);
	double g = func(b);

	for (int i = 1; i <= MAXSTEPS; i++) {
		if (f * g < 0.)
			return i;

		if (abs(f) < abs(g))
			f = func(a += 1.1 * (a - b));
		else
			g = func(b += 1.1 * (b - a));
	}

	return 0;
}

int main()
{
	MyFunc test(4);

	double x1 = 6.1;
	double x2 = 6.2;

	int steps = bracket(test, x1, x2);

	if (steps == 0)
		cout << "Calculation did not finish after " << MAXSTEPS << " steps!" << endl;
	else
		cout << "Calculation took " << steps << " steps.";
}
