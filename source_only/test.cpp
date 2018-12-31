#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <complex>
#include <gsl/gsl_sf_coupling.h>
#include <gsl/gsl_sf_gamma.h>

inline std::complex<double> gsl_sf_lngamma_complex(std::complex<double> x)
{
	gsl_sf_result lnr, arg;
	if (gsl_sf_lngamma_complex_e(real(x), imag(x), &lnr, &arg)) {
		printf("error!"); exit(1);
	}
	return std::complex<double>(lnr.val, arg.val);
}

int main()
{
	using namespace std;
	int two_ja = 1;
	int two_jb = 1;
	int two_jc = 0;
	int two_ma = 1;
	int two_mb = -1;
	int two_mc = 0;
	cout << "3j = " << gsl_sf_coupling_3j(two_ja, two_jb, two_jc, two_ma, two_mb, two_mc) << endl << endl;

	complex<double> in(1.5, 1.5), out;
	cout << "gammaC" << in << " = " << exp(gsl_sf_lngamma_complex(in)) << endl;
}
