#include <iostream>
#include <cmath>
#include "mnewton.h"
using namespace std;

class Equi {
	// Konstanter Druck-Parameter
	const double P;

	// Heiz-Funktion
	double gamma(const double rho, const double T) {
		return 14 * sqrt(rho) / T;
	}
	// Kühl-Funktion double lambda(const double rho, const double T) {
		return 0.5 * sqrt(T) / rho;
	}

	// Zustandsgleichung des (nichtidealen) Gases
	double eos(const double rho, const double T) {
		return P - 0.001 * (rho + 2 * rho * rho) * T;
	}

	//      Inverse Jacobi Matrix berechnen
	void inverse(double inv[2][2], const double rho, const double T) {
		// Jacobi-Matrix
		double j[2][2];
		j[0][0] = 0.5 * sqrt(T) / (rho * rho) + 7 / (T * sqrt(rho));
		j[1][1] = -(rho + 2 * rho * rho) / 1000;
		j[0][1] = -0.25 / (sqrt(T) * rho) - 14 * sqrt(rho) / (T * T);
		j[1][0] = -T * (1 + 4 * rho) / 1000;

		// reziproke Determinante der Jacobi-Matrix
		const double rdet = 1 / (j[0][0] * j[1][1] - j[0][1] * j[1][0]);

		// Inverse Jacobi-Matrix
		inv[0][0] = rdet * j[1][1];
		inv[1][1] = rdet * j[0][0];
		inv[0][1] = -rdet * j[0][1];
		inv[1][0] = -rdet * j[1][0];
	}

 public:
	// Konstruktor für Druck-Initialisierung
	Equi(const double P_in):P(P_in) {
	}

	// Funktions-Werte F(r) und das Produkt -inverse(jacobian)*F berechnen
	void operator() (const double r[], double F[], double j[]) {
		const double rho = r[0];
		const double T = r[1];

		// Komponenten der Vektor-Funktion F(x)
		F[0] = gamma(rho, T) - lambda(rho, T);
		F[1] = eos(rho, T);

		// Inverse Jacobi-Matrix berechnen
		double inv[2][2];
		inverse(inv, rho, T);

		// store the Newton vector j
		j[0] = -(F[0] * inv[0][0] + F[1] * inv[0][1]);
		j[1] = -(F[0] * inv[1][0] + F[1] * inv[1][1]);
	}
};

int main()
{
	Equi testSystem(20);

	double x[2] = { 10000, 10000 };	// Startwerte
	double F[2];

	const int steps = mnewt(testSystem, x, F);

	cout << "Anzahl der benötigten Iterationen: " << steps << endl;	// Für die vorgegeben Startwerte werden 20 Iterationen benötigt
	cout << "Lösungs-Vektor x: (" << x[0] << ", " << x[1] << ")" << endl;	// Die Lösung liegt bei x=(rho=10.1101, T=93.2238)
	cout << "Funktionswerte des Lösungsvektors F(x): (" << F[0] << ", " << F[1] << ")" << endl;	// Die Funktionswerte des Lösungsvektors sind F(x)=(1.66533*10^(-16), 0)
}
