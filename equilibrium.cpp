// **************************
// *** Numerikum, WS 2014 ***
// *** Sheet 04 Problem 3 ***
// **************************

// **********
class Equi {
//      Save the pressure as a constant parameter
	const double P;

//      TODO: implement the heating function Gamma
	double gamma(const double rho, const double T) {
	...}
//      TODO: implement the cooling function Lambda double lambda(const double rho, const double T) {
	...}

//      TODO: implement the Equation of state
	double eos(const double rho, const double T) {
	...}

//      Calculate inverse matrix
	void inverse(double inv[2][2], const double rho, const double T) {
		// TODO: implement the Jacobian matrix
		double j[2][2];
		...
		    // TODO: calculate the determinant
		    ...
		    // TODO: calculate the inverse matrix
	inv[0][0] = ... inv[1][1] = ... inv[0][1] = ... inv[1][0] = ...}

 public:
//      Constructor: assign value for pressure
	Equi(const double P_in):P(P_in) {
	}

//      Calculate function values F and -inverse(jacobian)*F
	void operator() (const double r[], double F[], double j[]) {
		const double rho = r[0];
		const double T = r[1];

		// TODO: store the two components of the vector function F(x)
		F[0] = ... F[1] = ...
		    // Obtain the inverse Jacobian matrix
		double inv[2][2];
		inverse(inv, rho, T);

		// TODO: store the Newton vector j (see exercise sheet)
	j[0] = ... j[1] = ...}
};
