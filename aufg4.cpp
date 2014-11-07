#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

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

int main()
{
	ofstream file("newton.txt", ios::trunc);	// Datei öffnen (und überschreiben)

	// x-Richtung
	for (int i = 0; i < 100; i++) {
		double x = i;	// TODO: Intervalle richtig machen

		// y-Richtung
		for (int j = 0; j < 100; j++) {
			double y = j;

			Z z(x, y);

			int convergence = 0;

			for (int k = 0; k < 100; k++) {
				// Newton-Schritt
				z -=;
			}

			// TODO: Konvergenz überprüfen
			if (0) {
				convergence = 1;
			}
			// Datei-Ausgabe
			file << z.x << '\t' << z.y << '\t' << convergence << '\n';
		}
	}

	file.close();		// Datei schließen
}
