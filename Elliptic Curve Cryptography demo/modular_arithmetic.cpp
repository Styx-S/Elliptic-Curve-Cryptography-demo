#include "modular_arithmetic.h"
using namespace mod;

int mod::modP(int n, int p) {
	if (n >= 0)
		return n % p;
	else {
		int k = (-n) % p;
		return p - k;
	}
}

int mod::modPAdd(int a, int b, int p) {
	return modP(modP(a, p) + modP(b, p), p);
}

int mod::modPMul(int a, int b, int p) {
	return modP(modP(a, p) * modP(b, p), p);
}

int mod::modPDiv(int a, int b, int p) {
	bool sign = 1;
	if (a < 0) {
		sign = -sign;
		a = -a;
	}
	if (b < 0) {
		sign = -sign;
		b = -b;
	}
	for (int i = 0; i < p; i++) {
		if ((a + i * p) % b == 0)
			return modP(sign * ((a + (i*p)) / b), p);
	}
}

int mod::modPPow(int a, int b, int p) {
	int result = 1;
	int base = modP(a, p);
	while (b--) {
		result *= base;
		result = modP(result, p);
	}
	return result;
}
