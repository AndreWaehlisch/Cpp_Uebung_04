#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

const double STEPS = 1000.;	// Durch Erhöhen der Auflösung in x- und y- Richtung und der Iterationsschritte um den Faktor 10, konvergieren mehr der Startwerte gegen die Nullstelle z=1.

// Komplexe Zahl mit z=x+i*y
class Z {
 public:

	double x, y;

	////////////////
	// Konstruktoren
	////////////////

	 Z() {
		x = 0;
		y = 0;
	} Z(const double x_in) {
		x = x_in;
		y = 0;
	}

	Z(const double x_in, const double y_in) {
		x = x_in;
		y = y_in;
	}

	///////////////////////
	// Operator-Overloading
	///////////////////////

	Z operator+(const Z & z) {
		Z c;
		c.x = (x + z.x);
		c.y = (y + z.y);
		return c;
	}

	Z operator-(const Z & z) {
		Z c;
		c.x = (x - z.x);
		c.y = (y - z.y);
		return c;
	}

	Z operator*(const Z & z) {
		Z c;
		c.x = (x * z.x - y * z.y);
		c.y = (x * z.y + y * z.x);
		return c;
	}

	Z operator/(const Z & z) {
		Z c;
		c.x = (x * z.x + y * z.y) / (z.x * z.x + z.y * z.y);
		c.y = (y * z.x - x * z.y) / (z.x * z.x + z.y * z.y);
		return c;
	}
};

// Testfunktion f(z)=z^3-1
Z testfunktion(Z & z)
{
	Z c;
	c.x = (z.x * z.x * z.x - 3 * z.x * z.y * z.y - 1);
	c.y = (3 * z.x * z.x * z.y - z.y * z.y * z.y);
	return c;
}

Z newtonSchritt(Z & z)
{
	Z c;
	Z F = testfunktion(z);

	// jacobian matrix
	const double j[2][2] = {
		{3 * (z.x * z.x - z.y * z.y), 6 * z.x * z.y},
		{-6 * z.x * z.y, 3 * (z.x * z.x - z.y * z.y)}
	};

	// inverse det
	const double id = 1 / (j[1][1] * j[0][0] - j[0][1] * j[1][0]);

	// inverse jacobian
	const double inverse[2][2] = {
		{id * j[1][1], -id * j[1][0]},
		{-id * j[0][1], id * j[0][0]}
	};

	c.x = (inverse[0][0] * F.x + inverse[0][1] * F.y);
	c.y = (inverse[1][0] * F.x + inverse[1][1] * F.y);

	return c;
}

int main()
{
	ofstream file("newton.txt", ios::trunc);	// Datei öffnen (und überschreiben)

	// x-Richtung
	for (int i = 0; i < STEPS; i++) {
		double x = i * 2 / (STEPS - 1) - 1;

		// y-Richtung
		for (int j = 0; j < STEPS; j++) {
			double y = j * 2 / (STEPS - 1) - 1;

			Z z(x, y);

			file << z.x << '\t' << z.y << '\t';

			for (int k = 0; k < STEPS; k++) {
				// Newton-Schritt
				z = z - newtonSchritt(z);
			}

			// Konvergenz überprüfen
			int convergence = 0;

			if (fabs(z.x - 1) < 1e-15) {
				convergence = 1;
			}
			// Datei-Ausgabe
			file << convergence << '\n';
		}
	}

	file.close();		// Datei schließen

	cout << "Output in 'newton.txt' geschrieben!" << endl;
}
