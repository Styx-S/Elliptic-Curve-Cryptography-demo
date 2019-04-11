#include "ECC_Cryptor.h"
#include "modular_arithmetic.h"
using namespace cryptography;
using namespace mod;

#include <string>
#include <cmath>
#include <cstdlib>
#include <ctime>
using std::string;
using std::pow;
using std::time;
using std::srand;
using std::rand;

void EllipticCurve::initAllPoints() {
	if (m_points.size() != 0)
		m_points.clear();
	m_init = true;
	for (int x = 0; x < m_p; x++) {
		//each point in this curve satisfy y^2 = x^3 + ax +b (mod p)
		int k = modPAdd(modPAdd(modPPow(x, 3, m_p), modPMul(x, m_a, m_p), m_p), m_b, m_p);
		for (int y = 0; y < m_p; y++) {
			if (k != modPPow(y, 2, m_p))
				continue;
			else m_points.push_back({ x,y });
		}
	}
}

int EllipticCurve::findPoint(const Point& aim) {
	int l = 0, r = m_points.size();
	while (l < r) {
		int mid = (l + r) / 2;
		const Point& p = m_points[mid];
		if (aim.a < p.a) {
			r = mid;
			continue;
		}
		else if (aim.a > p.a) {
			l = mid+1;
			continue;
		}
		else if (aim.b < p.b) {
			r = mid;
			continue;
		}
		else if (aim.b > p.b) {
			l = mid + 1;
		}
		else return mid;
	}
	return -1;
}

Point EllipticCurve::getPoint(int index) {
	if (index < 0 || index > m_points.size())
		throw string("index out of bound");
	return m_points[index];
}

Point EllipticCurve::add(const Point& p, const Point& q) {
	int k;
	if (p.a == q.a && p.b == q.b) {
		// k = (3pX^2 + a) / 2pY (mod p)
		k = modPDiv(modPAdd(modPMul(modPPow(q.a, 2, m_p), 3, m_p), m_a, m_p),
			modPMul(p.b, 2, m_p), m_p);
	}
	else {
		// k = (qY - pY) / (qX - pX) (mod p)
		k = modPDiv(modPAdd(q.b, -p.b, m_p), modPAdd(q.a, -p.a, m_p), m_p);
	}
	Point np;
	// npX = k^2 - pX - qX (mod p)
	// npY = k(px - npX) - pY (mod p)
	np.a = modPAdd(modPAdd(modPPow(k, 2, m_p), -p.a, m_p), -q.a, m_p);
	np.b = modPAdd(modPMul(k, modPAdd(p.a, -np.a, m_p), m_p), -p.b, m_p);
	return np;
}
Point EllipticCurve::mulK(const Point& a, int k) {
	vector<Point> result;
	Point p = a;
	k--;
	result.push_back(a);
	int n = 0;
	while (pow(2,n) < k) {
		result.push_back(this->add(result[n], result[n]));
		n++;
	}
	while (k) {
		int max = 0;
		for (int i = n; i >= 0; i--) {
			if ((int)(pow(2, i)) <= k) {
				max = i;
				break;
			}
		}
		p = this->add(p, result[max]);
		k -= pow(2,max);
	}
	return p;
}
Point EllipticCurve::minus(const Point& a) {
	Point p = a;
	p.b = modP(-p.b, m_p);
	return p;
}

Point ECC_Encryptor::chooseKG(int k, Point G) {
	m_ok = true;
	m_G = G;
	m_k = k;
	m_Q = m_curve.mulK(G, k);
	return m_Q;
}

Encryptor& ECC_Encryptor::operator<<(istream& inputSource) {
	srand(time(NULL));
	if (!m_ok)
		return *this;
	while (inputSource) {
		char ch = inputSource.get();
		if (ch == -1)break;
		int size = m_curve.getPointList().size();
		int r = rand() % size;
		Point M = m_curve.getPointList()[ch % size];
		Point pC1 = m_curve.add(M, m_curve.mulK(m_G, r));
		Point pC2 = m_curve.mulK(m_G, r);
		this->m_writeResult << pC1.a << " "<< pC1.b << " "<< pC2.a<< " " << pC2.b << " ";
	}
	return *this;
}

Decryptor& ECC_Decryptor::operator<<(istream& inputSource) {
	while (true) {
		Point pC1, pC2;
		inputSource >> pC1.a >> pC1.b >> pC2.a >> pC2.b;
		if (!inputSource)
			break;
		Point p = m_curve.add(pC1, m_curve.minus(pC2));
		char c = m_curve.findPoint(p);
		this->m_writeResult << c;
	}
	return *this;
}