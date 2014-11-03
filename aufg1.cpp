#include <iostream>
#include <cmath>
using namespace std;

int bracket(Functor & func, double &a, double &b)
{
	double f = func(a);
	double g = func(b);

	for (int i = 1; i <= 100; i++) {
		if (f * g < 0.)
			return i;

		if (abs(f) < abs(g))
			f = func(a += 1.1 * (a - b));
		else
			g = func(b += 1.1 * (b - 1));
	}
}

int main()
{

}
