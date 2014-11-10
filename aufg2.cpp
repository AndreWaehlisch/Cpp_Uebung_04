#include <iostream>
#include <cmath>
#include "brent.h"		// Van-Wijngaarden-Dekker-Brent-Algorithmus
using namespace std;

class MyFunc {
 public:

	double a;

	 MyFunc(const double init) {
		a = init;
	} double operator() (const double x) {
		return (sinh(x) / x - (a * x * x));
	}

	void printFunc() {
		if (a > 0)
			cout << "Gewählte Testfunktion: f(x) = sinh(x)/x-" << a << "x^2" << endl << endl;
		else
			cout << "Gewählte Testfunktion: f(x) = sinh(x)/x+" << ((-1) * a) << "x^2" << endl << endl;
	}
};

int main()
{
	cout << "Van-Wijngaarden-Dekker-Brent-Algorithmus" << endl;

	double x1 = 6.1, x2 = 8.04481, x3;

	MyFunc testFunktion(2);	// Klassen-Definition in brent.h
	testFunktion.printFunc();

	const int steps = brent(testFunktion, x1, x2, x3, 1e-14);

	cout << "Iterationen: " << steps << " Nullstelle x0=" << x3 << endl;	// Der Algorithmus benötigt lediglich 8 Iterationen (Schritte) bei den vorgegebenen Startwerten. Im Vergleich zu den 49 Iterationen vom einfachen Bisektions-Verfahren ist der Van-Wijngaarden-Dekker-Brent-Algorithmus zu bevorzugen.
}
