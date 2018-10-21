#ifndef __DES_H__
#define __DES_H__

#include <cstdio>
#include <string>
#include <cstring>
#include <iostream>


namespace DES {
	
	// ���ܹ�����Ҫ��һЩ����
	const extern int iteration_times;
	const extern unsigned short IP[64];
	const extern unsigned short IPinv[64];

	// F������Ҫ��һЩ����
	const extern unsigned short E[48];
	const extern unsigned short S[8][4][16];
	const extern unsigned short SP[32];

	// ��������Կ��Ҫ��һЩ����
	const extern unsigned short LeftShiftsNumber[16];
	const extern unsigned short PC1[56];
	const extern unsigned short PC2[48];


	class Key {
	public:
		Key();
		~Key();
		// ���캯��������C[], D[]
		Key(const unsigned long long &K);
		// ��ȡ����Կ��num: ����Կ�Ĳ���; mode: 1: ���ܣ�0: ����
		unsigned long long subKey(int num, int mode);
	private:
		unsigned long long key;
		// C,D �е�32λֻ�ýϵ͵�28λ
		unsigned int C[17], D[17]; 
	};

	/*
	* return: ���ܻ���ܺ�Ķ����ƴ���64λ
	*  M: ����64λ
	*  key: ��Կ
	*  mode: 1: ���ܣ� 0: ����
	*/
	unsigned long long coder(const unsigned long long &M, const unsigned long long &K, int mode);

	/*
	*  return: F�����ķ���ֵ��32λ�����ƴ�
	*  DES�е�F����������S-box
	*  R: ǰһ���R��32λ
	*  K: ����Կ��48λ
	*/
	unsigned long long F_funtion(const unsigned long long &R, const unsigned long long &K);

	/* 
	*  �û�����
	*  return: �û���Ķ����ƴ�
	*  arr: �û�����
	*  ansLen: �û�������ȣ������鳤��
	*  num: ԭbit����
	*  numLen: ԭbit���ȣ���num�Ķ�����λ��
	*/  
	unsigned long long permutation(const unsigned short *arr, int ansLen, const unsigned long long &num, int numLen);
	
	/*
	* ���ܺͽ��ܺ���
	* M: ����
	* S: ����
	* K: ��Կ
	*/
	unsigned long long encode(const unsigned long long &M, const unsigned long long &K);
	unsigned long long decode(const unsigned long long &S, const unsigned long long &K);

}


#endif // __DES_H__