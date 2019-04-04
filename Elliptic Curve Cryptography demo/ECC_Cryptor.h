#ifndef  ECC_CRYPTOR_H
#define ECC_CRYPTOR_H

#include "Cryptography.h"
namespace cryptography {
	/* y^2 = x^3 + ax + b (mod p)*/
	class EllipticCurve {
	public:
		EllipticCurve(int a, int b, int p) { m_a = a; m_b = b; m_p = p; }
	private:
		int m_a, m_b, m_p;
	};

	class ECC_Encryptor : public Encryptor {

	};

	class ECC_Decryptor : public Decryptor {

	};

}

#endif // ! ECC_CRYPTOR_H
