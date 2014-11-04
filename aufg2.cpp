#include <iostream>
#include <cmath>
#include "brent.h"		// Van-Wijngaarden-Dekker-Brent-Algorithmus
using namespace std;

int main()
{
	cout << "Van-Wijngaarden-Dekker-Brent-Algorithmus" << endl;

	double x1, x2, x3;

	x1 = 6.1;
	x2 = 8.04481;
	MyFunc testFunktion(2);
	testFunktion.printFunc();

	const int steps = brent(testFunktion, x1, x2, x3, pow(10, -14));

	cout << "Iterationen: " << steps << " Nullstelle x0=" << x3 << endl;	// Der Algorithmus benötigt lediglich 8 Iterationen (Schritte) bei den vorgegebenen Startwerten. Im Vergleich zu den 49 Iterationen vom einfachen Bisektions-Verfahren ist der Van-Wijngaarden-Dekker-Brent-Algorithmus zu bevorzugen.
}
