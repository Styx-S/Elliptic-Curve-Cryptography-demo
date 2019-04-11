#include "ECC_Cryptor.h"
using namespace cryptography;
#include "modular_arithmetic.h"
using namespace mod;
#include <iostream>
using std::cout;
using std::endl;
using std::cin;

void showPoint(const Point& p) {
	cout << "(" << p.a << ", " << p.b << ")";
}
int main() {
	EllipticCurve curve(1,1,19);
	const vector<Point>& pList= curve.getPointList();
	for (int i = 0; i < pList.size(); i++) {
		const Point& p = pList[i];
		cout << "[" << i << "]";
		showPoint(p);
		cout << endl;
	}
	int pa, pb;
	cin >> pa >> pb;
	Point result = curve.add(pList[pa], pList[pb]);
	showPoint(result);
	cout << endl;

	int pause;
	cin >> pause;
}