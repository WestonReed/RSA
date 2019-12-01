#ifndef RSA_H
#define RSA_H

#include <gmp.h>

class RSA{
private:
	mpz_t p, q, d, n, e;
public:
	RSA(int bitlength); //generate new key
	RSA(const char* _p, const char* _q); //build key given private key
	void decrypt(mpz_t rot, mpz_t c); //find m given c, with RSA private key
	void exportPrivKey(); //export the private bits
	void encryptPub(mpz_t rot, mpz_t m);
	__mpz_struct* getPubN(){return n;}
	__mpz_struct* getPubE(){return e;}
};

void encrypt(mpz_t rot, mpz_t m, mpz_t n, mpz_t e); //encrypt with public key
std::string encode(std::string s);

#endif
