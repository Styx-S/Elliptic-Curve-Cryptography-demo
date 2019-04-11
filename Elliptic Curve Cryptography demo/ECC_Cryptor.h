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
		Point minus(const Point& a);
		const vector<Point>& getPointList() { return m_points; }
	private:
		void initAllPoints(); 
		bool m_init; // set true in initAllPoints function
		int m_a, m_b, m_p;
		vector<Point> m_points;
	};

	class ECC_Encryptor : public Encryptor {
	public: 
		ECC_Encryptor(ostream& writeResult, EllipticCurve curve) : Encryptor(writeResult), m_curve(curve) { m_ok = false; }
		virtual Encryptor& operator<<(istream& inputSource);
		Point chooseKG(int k, Point G);
	private:
		bool m_ok;
		int m_k;
		Point m_G;
		Point m_Q;
		EllipticCurve m_curve;
	};

	class ECC_Decryptor : public Decryptor {
	public:
		ECC_Decryptor(ostream& writeResult, EllipticCurve curve, Point Q, Point G) : Decryptor(writeResult), m_curve(curve) {}
		virtual Decryptor& operator<<(istream& inputSource);
	private:
		EllipticCurve m_curve;
	};

}

#endif // ! ECC_CRYPTOR_H
