#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>
#include <fstream>

#include "des.h"

using namespace std;
bool in_text[10010];
bool key[100];
bool out_text[10010];
void read(bool *arr, ifstream &input, int &len)
{
	char ch;
	len = 0;
	while (input >> ch && ch != '0' && ch != '1');
	arr[len++] = ch == '1';
	while (input >> ch && (ch == '0' || ch == '1')) 
		arr[len++] = ch == '1';
}

void des_cbc(bool *arr, int len, bool *key, ofstream &output, unsigned long long coder(const unsigned long long &, const unsigned long long &), int mode)
{
	unsigned long long num = 0;
	unsigned long long temp = 0;
	unsigned long long ullkey = 0;

	for (int i = 0; i < 64; i++)
		ullkey = ullkey << 1 | (unsigned long long)key[i];

	for (int i = 0; i < len; i += 64) {

		num = 0;
		for (int j = 0; j < 64; j++)
			num = num << 1 | (unsigned long long)arr[i + j];

		// encode, 先与前一段结果异或，再加密
		if (mode == 0)
			num ^= temp;
		
		unsigned long long ans = coder(num, ullkey);
		
		// decode，先解密，再与前一段结果异或
		if (mode == 1)
			ans ^= temp;

		// 输出到output.txt
		for (int j = 0; j < 64; j++)
			output << ((ans >> (63 - j)) & 1);
		
		if (mode == 0) temp = ans;
		if (mode == 1) temp = num;
	}
	cout << "OK!" << endl;
}

int main()
{
	ofstream output("testData/output.txt");
	ifstream input_cipher("testData/input_cipher.txt");
	ifstream input_ciphertext("testData/input_ciphertext.txt");
	ifstream input_plaintext("testData/input_plaintext.txt");

	int mode = 0;
	cout << "DES Algorithm!" << endl;
	cout << "please enter the coder mode" << endl;
	cout << "encode: 0" << endl;
	cout << "decode: 1" << endl;
	cout << "mode: ";
	cin >> mode;
	
	int text_len = 0, key_len = 64;
	read(key, input_cipher, key_len);
	read(in_text, mode ? input_ciphertext : input_plaintext, text_len);
	
	//将二进制长度扩展至64的倍数
	text_len = ((text_len - 1) / 64 + 1) * 64;

	//cout << text_len << endl;
	//加密或解密

	des_cbc(in_text, text_len, key, output, mode ? DES::decode : DES::encode, mode);

	system("pause");
	return 0;
}
