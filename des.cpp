#include "des.h"


// #define _DEGUB_

using namespace std;

namespace DES {

	const int iteration_times = 8;

	const unsigned short IP[] = { 57, 49, 41, 33, 25, 17, 9, 1, 59, 51, 43, 35, 27, 19, 11, 3,  \
								61, 53, 45, 37, 29, 21, 13, 5, 63, 55, 47, 39, 31, 23, 15, 7, \
								56, 48, 40, 32, 24, 16, 8, 0, 58, 50, 42, 34, 26, 18, 10, 2,  \
								60, 52, 44, 36, 28, 20, 12, 4, 62, 54, 46, 38, 30, 22, 14, 6, \
	};

	const unsigned short IPinv[] = { 39, 7, 47, 15, 55, 23, 63, 31, 38, 6, 46, 14, 54, 22, 62, 30, \
								   37, 5, 45, 13, 53, 21, 61, 29, 36, 4, 44, 12, 52, 20, 60, 28, \
								   35, 3, 43, 11, 51, 19, 59, 27, 34, 2, 42, 10, 50, 18, 58, 26, \
								   33, 1, 41, 9, 49, 17, 57, 25, 32, 0, 40, 8, 48, 16, 56, 24,   \
	};

	/* ******************************************************************* */

	const unsigned short E[] = { 31, 0, 1, 2, 3, 4, 3, 4, 5, 6, 7, 8, 7, 8, 9, 10, \
									11, 12, 11, 12, 13, 14, 15, 16, 15, 16, 17, 18, 19, 20, 19, 20, \
									21, 22, 23, 24, 23, 24, 25, 26, 27, 28, 27, 28, 29, 30, 31, 0, \
	};

	const unsigned short SP[] = { 15, 6, 19, 20, 28, 11, 27, 16, 0, 14, 22, 25, 4, 17, 30, 9, \
									1, 7, 23, 13, 31, 26, 2, 8, 18, 12, 29, 5, 21, 10, 3, 24 \
	};

	const unsigned short S[8][4][16] = {
		{{14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
		 {0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
		 {4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
		 {15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13}},
		{{15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10},
		 {3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5},
		 {0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15},
		 {13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9}},
		{{10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8},
		 {13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1},
		 {13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7},
		 {1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12}},
		{{7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15},
		 {13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9},
		 {10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4},
		 {3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14}},
		{{2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9},
		 {14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6},
		 {4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14},
		 {11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3}},
		{{12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11},
		 {10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8},
		 {9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6},
		 {4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13}},
		{{4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1},
		 {13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6},
		 {1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2},
		 {6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12}},
		{{13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7},
		 {1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2},
		 {7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8},
		 {2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11}}
	};

	/* ******************************************************************* */

	const unsigned short LeftShiftsNumber[] = { 1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1 };

	const unsigned short PC1[] = { 56, 48, 40, 32, 24, 16, 8, 0, 57, 49, 41, 33, 25, 17, 9, 1, \
									58, 50, 42, 34, 26, 18, 10, 2, 59, 51, 43, 35, 62, 54, 46, 38, \
									30, 22, 14, 6, 61, 53, 45, 37, 29, 21, 13, 5, 60, 52, 44, 36,  \
									28, 20, 12, 4, 27, 19, 11, 3, \
	};

	const unsigned short PC2[] = { 13, 16, 10, 23, 0, 4, 2, 27, 14, 5, 20, 9, 22, 18, 11, 3, \
									25, 7, 15, 6, 26, 19, 12, 1, 40, 51, 30, 36, 46, 54, 29, 39, \
									50, 44, 32, 47, 43, 48, 38, 55, 33, 52, 45, 41, 49, 35, 28, 31, \
	};



	/* ******************************************************************* */

	Key::Key() {}
	Key::~Key() {}

	Key::Key(const unsigned long long &K)
	{
		key = K;
		// 求C[0],D[0]
		unsigned long long ip = permutation(PC1, 56, key, 64);
		C[0] = unsigned int(ip >> 28);
		D[0] = unsigned int(ip & ((1 << 28) - 1));

		// 求C[i],D[i]
		unsigned int mask = (1 << 28) - 1;
		for (int i = 0; i < iteration_times; i++) {
			C[i + 1] = (C[i] << LeftShiftsNumber[i] & mask) | C[i] >> (28 - LeftShiftsNumber[i]);
			D[i + 1] = (D[i] << LeftShiftsNumber[i] & mask) | D[i] >> (28 - LeftShiftsNumber[i]);
		}
	}

	unsigned long long DES::Key::subKey(int num, int mode)
	{
		unsigned long long subkey = 0;
		if (!mode) num = iteration_times - num + 1;
		unsigned long long c = C[num], d = D[num];
		unsigned long long K = c << 28 | d;
		subkey = permutation(PC2, 48, K, 56);
		return subkey;
	}

	unsigned long long DES::coder(const unsigned long long &M, const unsigned long long &K, int mode)
	{
		unsigned long long ip = 0;
		unsigned long long L, R, RL = 0;
		unsigned long long ans = 0;
		Key key(K);
		ip = permutation(IP, 64, M, 64);
		L = ip >> 32;
		R = ip & (((unsigned long long)1 << 32) - 1);

		// 迭代iteration_times次(8次)
		for (int i = 0; i < iteration_times; i++) {
			unsigned long long temp = R;
			unsigned long long Ki = key.subKey(i + 1, mode);
			R = L ^ F_funtion(R, Ki);
			L = temp;
		}

		RL = R << 32 | L;
		ans = permutation(IPinv, 64, RL, 64);
		return ans;
	}

	unsigned long long F_funtion(const unsigned long long &R, const unsigned long long &K)
	{
		unsigned long long exR = 0, xorNum;
		unsigned long long ans = 0;
		//32bits扩展至48bits
		exR = permutation(E, 48, R, 32);
		//扩展后的R与子秘钥Ki异或
		xorNum = exR ^ K;

		//分成8个S-box，每个box将6bits压缩到4bits
		for (int i = 0; i < 8; i++) {
			unsigned int Bi = (xorNum >> ((7 - i) * 6)) & 0x3f;
			unsigned int x = ((Bi >> 5 & 1) << 1) | (Bi & 1);
			unsigned int y = (Bi >> 1) & 0xf;
			ans = ans << 4 | S[i][x][y];
		}
		ans = permutation(SP, 32, ans, 32);
		return ans;
	}

	unsigned long long permutation(const unsigned short *arr, int ansLen, const unsigned long long &num, int numLen)
	{
		unsigned long long ans = 0;
		for (int i = 0; i < ansLen; i++)
			ans = ans << 1 | num >> (numLen - 1 - arr[i]) & 1;
		return ans;
	}

	unsigned long long encode(const unsigned long long &M, const unsigned long long &K) { return coder(M, K, 1); }
	unsigned long long decode(const unsigned long long &S, const unsigned long long &K) { return coder(S, K, 0); }
}

#ifdef _DEGUB_
int main()
{
	unsigned long long K = (unsigned long long)0x133457799BBCDFF1;
	unsigned long long M = (unsigned long long)0x0123456789ABCDEF;
	unsigned long long S = (unsigned long long)0x85E813540F0AB405;
	// DES::Key key(K);
	cout << hex << DES::encode(M, K) << endl;
	cout << hex << DES::decode(S, K) << endl;
	system("pause");
	return 0;
}
#endif // DEGUB