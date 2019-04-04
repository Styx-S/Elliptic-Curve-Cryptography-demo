#ifndef CRYPTOGRAPHY_H
#define CRYPTOGRAPHY_H

#include <iostream>
using std::istream;
using std::ostream;
namespace cryptography {
	class BaseCryptor {
	public:
		BaseCryptor(ostream& writeResult) : m_writeResult(writeResult) {}
		~BaseCryptor() {}
		virtual BaseCryptor& operator<<(istream& inputSource) = 0;
	protected:
		ostream& m_writeResult;
	};

	class Encryptor : public BaseCryptor {
	public:
		Encryptor(ostream& writeResult) : BaseCryptor(writeResult) {}
	};

	class Decryptor : public BaseCryptor {
	public:
		Decryptor(ostream& writeResult) : BaseCryptor(writeResult) {}
	};

}
#endif