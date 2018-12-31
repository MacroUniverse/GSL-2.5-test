#include <stdio.h>
#include <gsl/gsl_sf_coupling.h>

int main()
{
	int two_ja = 1;
	int two_jb = 1;
	int two_jc = 0;
	int two_ma = 1;
	int two_mb = -1;
	int two_mc = 0;
	printf("%f", gsl_sf_coupling_3j(two_ja, two_jb, two_jc, two_ma, two_mb, two_mc));
	//cout << isnan(1);
	//cout << isinf(1);
	//cout << isfinite(1)
	return 0;
}
