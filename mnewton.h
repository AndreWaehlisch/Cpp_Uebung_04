#ifndef _MNEWTON_H_
#define _MNEWTON_H_

#include <cmath>

// Implementation of the multidimensional Newton-Raphson method
// Numerical root finding of any functor that supports calls
// according to func(double x[], double y[], double j[])

// **********
template <class T>
int mnewt(T& func, double x[], double y[])
{
	static const int n = 2;
	static const int ntrial = 1000;
	static double tolx = 1e-15;
	static double toly = 1e-15;

	double j[n];
	for (int i=0; i<ntrial; ++i)
	{
		func(x,y,j);

		double erry = 0.;
		for (int k=0; k<n; ++k)
			erry += std::abs(y[k]);

		if (erry <= toly)
			return i;

		double errx = 0.;
		for (int k=0; k<n; ++k)
		{
			errx += std::abs(j[k]);
			x[k] += j[k];
		}

		if (errx <= tolx)
			return i;
	}

	std::cerr << "Maximum number of iterations has been reached!" << std::endl;
	return 0;
}

#endif
