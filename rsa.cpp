#include "rsa.h"
#include <math.h>
#include <iostream>
#include <cstdlib>
#include <algorithm>

//perform k primaility tests on a prime candidate pc
bool millerRabin(int pc, int k=100){
	if(pc==2 || pc==3)
		return true;
	if(pc<=1 || pc%2 == 0)
		return false;

	int s = 0;
	int r = pc-1;

	while(r & 1 == 0){
		s++;
		r = floor(r/2);
	}

	for(int i=0; i<k; ++i){
		int a = rand()%pc+2; //random number from 2 to n-1
		int x = fastPower(a, r, pc);
		if(x!=1 && x!=pc-1){
			int j = 1;
			while(j < s && x != pc-1){
				x = fastPower(x, 2, pc);
				if(x == 1)
					return false;
				j++;
			}
			if(x != pc-1)
				return false;
		}
	}

	return true;
}

int fastPower(long long a, unsigned long long b, int p){
	long long ret = 1;
	a %= p;
	while(b > 0){
		if(b & 1)
			ret = (ret*a) % p;
		b /= 2;
		a = (a*a) % p;
	}
	return (int)ret;
}

int modInv(int a, int m){
	a = a%m; 
    for (int x=1; x<m; x++) 
		if ((a*x) % m == 1) 
			return x; 
}

RSA::RSA(){
	//generate key
	srand(time(NULL));
	p = rand()%10000+1000;
	while(!millerRabin(p))
		p++;
	q=p-1000;
	while(!millerRabin(q) || q==p)
		q++;

	int phi = (p-1) * (q-1);
	e = 2;
	while(std::__gcd(e, phi) != 1)
		e++;
	
	n = p*q;
	d = modInv(e, (p-1)*(q-1));
}

RSA::RSA(int _p, int _q, int _e){
	//build key
	p = _p;
	q = _q;
	e = _e;
	n = p*q;
	d = modInv(e, (p-1)*(q-1));
}

int RSA::decrypt(int c){
	return fastPower(c, d, n);
}

void RSA::exportPrivKey(){
	std::cout << "p = " << p << std::endl;
	std::cout << "q = " << q << std::endl;
	std::cout << "e = " << e << std::endl;
	std::cout << "d = " << d << std::endl;
	std::cout << "n = " << n << std::endl; 
}

int RSA::encryptPub(int m){
	return encrypt(m, e, n);
}

int encrypt(int m, int n, int e){
	return fastPower(m, e, n);
}
