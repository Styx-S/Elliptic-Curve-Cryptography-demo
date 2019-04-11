#ifndef MODULAR_ARITHMETIC_H
#define MODULAR_ARITHMETIC_H

namespace mod {
	// assume p is positive number

	/* negative number also can be mod */
	int modP(int n, int p);

	/* return (a + b)(mod p)*/
	int modPAdd(int a, int b, int p);

	int modPMul(int a, int b, int p);

	int modPDiv(int a, int b, int p);

	/* return a^b (mod p)*/
	int modPPow(int a, int b, int p);

}

#endif // !MODULAR_ARITHMETIC_H
