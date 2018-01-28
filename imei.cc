#include <iomanip>
#include <sstream>
#include <string>

#include "ib/logger.h"
#include <openssl/md5.h>
#include <openssl/sha.h>

using namespace ib;
using namespace std;

int main(int argc, char** argv) {
	map<char, int> l1, l2;
	l1['0'] = 0;
	l1['1'] = 1;
	l1['2'] = 2;
	l1['3'] = 3;
	l1['4'] = 4;
	l1['5'] = 5;
	l1['6'] = 6;
	l1['7'] = 7;
	l1['8'] = 8;
	l1['9'] = 9;
	l2['0'] = 0;
	l2['1'] = 2;
	l2['2'] = 4;
	l2['3'] = 6;
	l2['4'] = 8;
	l2['5'] = 1;
	l2['6'] = 3;
	l2['7'] = 5;
	l2['8'] = 7;
	l2['9'] = 9;
	if (argc < 2) {
		Logger::error("usage: % [tac]", argv[0]);
		return -1;
	}

	string tac = argv[1];
	if (tac.length() != 8) {
		Logger::error("invalid tac %, not 8 digits long");
		return -1;
	}
	for (int i = 0; i < 8; ++i) {
		if (tac[i] < '0' || tac[i] > '9') {
			Logger::error("tac not a number.");
			return -1;
		}
	}

	for (size_t i = 0; i < 1000000; ++i) {
		uint8_t md[MD5_DIGEST_LENGTH];
		stringstream ss;
		ss << tac;
		ss << setfill('0');
		ss << setw(6);
		ss << i;

		int luhn = 0;
		assert(ss.str().length() == 14);
		for (size_t j = 0; j < 14; ++j) {
			if (!(j % 2)) luhn += l1[ss.str().at(j)];
			else luhn += l2[ss.str().at(j)];
		}
		luhn *= 9;
		luhn %= 10;
		ss << setw(1);
		ss << luhn;

		MD5((uint8_t *) ss.str().c_str(), ss.str().length(), md);
		cout << ss.str() << "," << Logger::hexify(md, MD5_DIGEST_LENGTH) << endl;
	}
}
