#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <complex>
#include <gsl/gsl_sf_coupling.h>
#include <gsl/gsl_sf_gamma.h>
#include <gsl/gsl_sf_legendre.h>

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
	int two_ja = 1, two_ma = 1;
	int two_jb = 1, two_mb = -1;
	int two_jc = 0, two_mc = 0;

	// should be 1/sqrt(2) = 0.707107...
	cout << "3j = " << gsl_sf_coupling_3j(two_ja, two_jb, two_jc, two_ma, two_mb, two_mc) << endl << endl;

	int two_jd, two_je, two_jf, two_jg, two_jh, two_ji;
	// {ja jb jc
	//  jd je jf
	//  jg jh ji}
	two_ja = 6; two_jb = 4, two_jc = 2;
	two_jd = 8; two_je = 2; two_jf = 4;
	two_jg = 0; two_jh = 6; two_ji = 4;
	
	// should be 0
	cout << "9j = " << gsl_sf_coupling_9j(two_ja, two_jb, two_jc, two_jd, two_je, two_jf, two_jg, two_jh, two_ji) << endl;

	complex<double> in(1.5, 1.5), out;
	cout << "gammaC" << in << " = " << exp(gsl_sf_lngamma_complex(in)) << endl;

	int lmax = 3;
	int n = gsl_sf_legendre_array_n(lmax);
	double *legen_arr = new double[n];
	gsl_sf_legendre_array(GSL_SF_LEGENDRE_NONE, lmax, 0.6, legen_arr);
	cout.precision(17);
	cout << "legendre polynomial P_3_2(0.6) = " << legen_arr[gsl_sf_legendre_array_index(3, 2)] << endl;
	delete[] legen_arr;
}
