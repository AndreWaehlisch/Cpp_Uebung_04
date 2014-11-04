#include <iostream>
#include <cmath>
using namespace std;

const int MAXSTEPS = 100;	//Max. Anzahl an Iterationen für die verwendeten Algorithmen

class MyFunc {
 public:

	double a;

	 MyFunc(double init) {
		a = init;
	} double operator() (double x) {
		return (sinh(x) / x - (a * x * x));
	}

	void printFunc() {
		if (a > 0)
			cout << "Gewählte Testfunktion: f(x) = sinh(x)/x-" << a << "x^2" << endl << endl;
		else
			cout << "Gewählte Testfunktion: f(x) = sinh(x)/x+" << ((-1) * a) << "x^2" << endl << endl;
	}
};

// Einklammern: Verschiebt 2 Startwerte (a, b) solange bis die Funktionswerte an den Stellen a und b verschiedene Vorzeichen haben.
int bracket(MyFunc & func, double &a, double &b)
{
	double f = func(a);
	double g = func(b);

	for (int i = 1; i <= MAXSTEPS; i++) {
		if (f * g < 0) {
			return i;
		}

		if (fabs(f) < fabs(g))
			f = func(a += (1.1 * (a - b)));
		else
			g = func(b += (1.1 * (b - a)));
	}

	return 0;		// Error: Berechnung abgebrochen
}

// Bisektions-Verfahren: Halbiere das Intervall zwischen zwei Startwerten a und b (deren Funktionswerte unterschiedliches Vorzeichen haben) bis eine Nullstelle der Funktion (näherungsweise) gefunden ist.
int bisection(MyFunc & func, double &a, double &b, double &c, const double tolerance)
{
	for (int i = 1; i <= MAXSTEPS; i++) {
		c = (a + b) / 2;	// Mitte des aktuellen Intervalls
		const double fc = func(c);	// Funktionswert an dieser Stelle

		if (fc == 0 || (b - a) < tolerance)	// Verlasse die Schleife wenn das Ergebnis gefunden ist. Die Nullstelle gilt auch als "gefunden", sofern die Intervall-Breite kleiner als die angegebene Toleranz ist.
			return i;

		// Aktuelles Intervall so verschieben, dass a und b weiterhin Funktionswerte mit unterschiedlichem Vorzeichen besitzen.
		if (func(c) * func(b) < 0)
			a = c;
		else
			b = c;
	};

	return 0;		// Error: Berechnung abgebrochen
}

int TuEinklammern(MyFunc & func, double &x1, double &x2)
{
	cout << "Starte das Einklammern mit Startwerten x1=" << x1 << " und x2=" << x2 << endl;

	const int stepsBracket = bracket(func, x1, x2);

	if (!stepsBracket) {
		cout << "Einklammer-Algorithmus wurde abgebrochen nach " << MAXSTEPS << " Schritten!" << endl;
		return 0;
	}

	cout << "Einklammern abgeschlossen nach " << stepsBracket << " Schritt(en). Eine Nullstelle sollte zwischen x1=" << x1 << " und x2=" << x2 << " liegen." << endl << endl;

	return stepsBracket;
}

int TuBisektion(MyFunc & func, double &x1, double &x2, const double tolerance)
{
	cout << "Starte nun das Biseketions-Verfahren." << endl;

	double ergebnis;
	const int stepsBisection = bisection(func, x1, x2, ergebnis, tolerance);

	if (!stepsBisection) {
		cout << "Bisektions-Verfahren wurde abgerbochen nach " << MAXSTEPS << " Schritten!" << endl;
		return 0;
	}

	cout << "Bisektions-Verfahren nach " << stepsBisection << " Schritt(en) abgeschlossen. Die gefundene Nullstelle liegt bei x0=" << ergebnis << " [mit einer Toleranz der Intervallbreite von " << tolerance << " ist der Funktionswert an dieser Stelle f(x0)=" << func(ergebnis) << " ]" << endl << endl;

	return stepsBisection;
}

void TuNullStelleFinden(MyFunc & func, const double startwert1, const double startwert2, const double tolerance)
{
	double x1 = startwert1;
	double x2 = startwert2;

	if (TuEinklammern(func, x1, x2))
		TuBisektion(func, x1, x2, tolerance);
}

int main()
{
	double startwert1, startwert2;

	startwert1 = 6.1;
	startwert2 = 6.2;
	MyFunc testFunktion1(4);
	testFunktion1.printFunc();
	TuEinklammern(testFunktion1, startwert1, startwert2);	// Das Einklammern ist nach 8 Iterationen (Schritten) beendet. Die gefundenen Werte sind: x1=-11.8109 und x2=6.2

	startwert1 = 6.1;
	startwert2 = 6.2;
	MyFunc testFunktion2(2);
	testFunktion2.printFunc();
	TuNullStelleFinden(testFunktion2, startwert1, startwert2, pow(10, -14));	// Das Bisektions-Verfahren liefert als Nullstelle x0=7.38441. Dieses Ergebnis ist nach 49 Schritten erreicht und liegt in Wahrheit bei f(x0)=-1.7053e-13

	startwert1 = 6.1;
	startwert2 = 6.2;
	MyFunc testFunktion3(-1);
	testFunktion3.printFunc();
	TuNullStelleFinden(testFunktion3, startwert1, startwert2, pow(10, -4));	// Für den gewählten Parameter a=-1 beendet der Algorithmus sich nach der Maximalzahl der angegeben Iterationen und findet keine Lösung. Damit lässt sich vermuten, dass diese Funktion keine Nullstellen auf der reellen Achse hat. (Sie hat wirklich nur zwei komplexe Nullstellen.)
}
