#include <iostream>
#include <gsl/gsl_sf_coupling.h>

int main()
{
	using namespace std;
	int two_ja = 1;
	int two_jb = 1;
	int two_jc = 0;
	int two_ma = 1;
	int two_mb = -1;
	int two_mc = 0;
	cout << gsl_sf_coupling_3j(two_ja, two_jb, two_jc, two_ma, two_mb, two_mc);
	cout << endl;
	//cout << isnan(1);
	//cout << isinf(1);
	//cout << isfinite(1)
}
