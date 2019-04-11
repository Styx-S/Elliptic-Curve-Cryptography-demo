#include "ECC_Cryptor.h"
using namespace cryptography;
#include "modular_arithmetic.h"
using namespace mod;
#include <iostream>
#include <fstream>
using std::cout;
using std::endl;
using std::cin;
using std::ifstream;
using std::ofstream;

void showPoint(const Point& p) {
	cout << "(" << p.a << ", " << p.b << ")";
}
int main() {
	EllipticCurve curve(1,1,173);
	//const vector<Point>& pList= curve.getPointList();
	//for (int i = 0; i < pList.size(); i++) {
	//	const Point& p = pList[i];
	//	cout << "[" << i << "]";
	//	showPoint(p);
	//	cout << endl;
	//}
	//int pa, pb;
	//cin >> pa >> pb;
	//Point result = curve.add(pList[pa], pList[pb]);
	//showPoint(result);
	//cout << endl;
	ifstream fsource, ifsecret;
	ofstream ofsecret;
	fsource.open("source.dat");
	ofsecret.open("secret.dat");
	ECC_Encryptor enc(ofsecret, curve);
	Point Q = enc.chooseKG(5, curve.getPointList()[5]);
	enc << fsource;
	ofsecret.close();
	ifsecret.open("secret.dat");
	ECC_Decryptor dec(cout, curve, Q, curve.getPointList()[5]);
	dec << ifsecret;

	int pause;
	cin >> pause;
}