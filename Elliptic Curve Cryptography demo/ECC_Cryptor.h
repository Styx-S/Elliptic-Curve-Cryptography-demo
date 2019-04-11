#ifndef  ECC_CRYPTOR_H
#define ECC_CRYPTOR_H

#include "Cryptography.h"

#include <vector>
using std::vector;
namespace cryptography {
	struct Point {
		int a;
		int b;
	};

	/* y^2 = x^3 + ax + b (mod p)*/
	class EllipticCurve {
	public:
		EllipticCurve() { m_init = false; }
		EllipticCurve(int a, int b, int p) { m_a = a; m_b = b; m_p = p; initAllPoints(); }
		int findPoint(const Point& aim);
		Point getPoint(int index);
		Point add(const Point& a, const Point& b);
		Point mulK(const Point& a, int k);
		const vector<Point>& getPointList() { return m_points; }
	private:
		void initAllPoints(); 
		bool m_init; // set true in initAllPoints function
		int m_a, m_b, m_p;
		vector<Point> m_points;
	};

	class ECC_Encryptor : public Encryptor {

	};

	class ECC_Decryptor : public Decryptor {

	};

}

#endif // ! ECC_CRYPTOR_H
