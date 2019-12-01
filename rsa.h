#ifndef RSA_H
#define RSA_H

class RSA{
private:
	int e;
	long long p, q, d;
	unsigned long long n;
public:
	RSA(); //generate new key
	RSA(int _p, int _q, int _e); //build key given private key
	int decrypt(int c); //find m given c, with RSA private key
	void exportPrivKey(); //export the private bits
	int encryptPub(int m);
	int getPubN(){return n;}
	int getPubE(){return e;}
};

int encrypt(int m, int n, int e); //encrypt with public key
int modInv(int a, int m); //computes the modular inverse a^-1 mod m
int fastPower(long long a, unsigned long long b, int p); //computes a^b mod p
bool millerRabin(int pc, int k);


#endif
