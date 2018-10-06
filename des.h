#ifndef __DES_H__
#define __DES_H__

#include <cstdio>
#include <string>
#include <cstring>
#include <iostream>


namespace DES {
	
	// 加密过程需要的一些常量
	const extern int iteration_times;
	const extern unsigned short IP[64];
	const extern unsigned short IPinv[64];

	// F函数需要的一些常量
	const extern unsigned short E[48];
	const extern unsigned short S[8][4][16];
	const extern unsigned short SP[32];

	// 生成子秘钥需要的一些常量
	const extern unsigned short LeftShiftsNumber[16];
	const extern unsigned short PC1[56];
	const extern unsigned short PC2[48];


	class Key {
	public:
		Key();
		~Key();
		// 构造函数，生成C[], D[]
		Key(const unsigned long long &K);
		// 获取子秘钥，num: 子秘钥的层数; mode: 1: 加密，0: 解密
		unsigned long long subKey(int num, int mode);
	private:
		unsigned long long key;
		// C,D 中的32位只用较低的28位
		unsigned int C[17], D[17]; 
	};

	/*
	* return: 加密或解密后的二进制串，64位
	*  M: 输入64位
	*  key: 秘钥
	*  mode: 1: 加密， 0: 解密
	*/
	unsigned long long coder(const unsigned long long &M, const unsigned long long &K, int mode);

	/*
	*  return: F函数的返回值，32位二进制串
	*  DES中的F函数，包含S-box
	*  R: 前一层的R，32位
	*  K: 子秘钥，48位
	*/
	unsigned long long F_funtion(const unsigned long long &R, const unsigned long long &K);

	/* 
	*  置换函数
	*  return: 置换后的二进制串
	*  arr: 置换数组
	*  ansLen: 置换结果长度，即数组长度
	*  num: 原bit序列
	*  numLen: 原bit长度，即num的二进制位数
	*/  
	unsigned long long permutation(const unsigned short *arr, int ansLen, const unsigned long long &num, int numLen);
	
	/*
	* 加密和解密函数
	* M: 明文
	* S: 密文
	* K: 秘钥
	*/
	unsigned long long encode(const unsigned long long &M, const unsigned long long &K);
	unsigned long long decode(const unsigned long long &S, const unsigned long long &K);

}



#endif // __DES_H__