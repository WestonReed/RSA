#include "rsa.h"
#include <math.h>
#include <iostream>
#include <cstdlib>
#include <algorithm>

RSA::RSA(int bitlength){
	//generate key
	mpz_t max;
	mpz_init(max);
	mpz_ui_pow_ui(max, 2, bitlength);
	mpz_init_set_ui(e, 65537);
	gmp_randstate_t state;
	gmp_randinit_default(state);
	srand(time(NULL));
	gmp_randseed_ui(state, rand());
	mpz_init(p);
	mpz_urandomm(p, state, max);
	mpz_nextprime(p, p);
	mpz_init_set(q, p);
	mpz_nextprime(q, q);
	mpz_init(n);
	mpz_mul(n, p, q);
	mpz_t p_minus_1, q_minus_1, phi;
	mpz_init(p_minus_1);
	mpz_init(q_minus_1);
	mpz_init(phi);
    mpz_sub_ui(p_minus_1, p, 1);
    mpz_sub_ui(q_minus_1, q, 1);
    mpz_mul(phi, p_minus_1, q_minus_1);
	mpz_invert(d, e, phi);
	gmp_randclear(state);
}

RSA::RSA(const char* _p, const char* _q){
	//build key
	mpz_init_set_str(p, _p, 10);
	mpz_init_set_str(q, _q, 10);
	mpz_init_set_ui(e, 65537);
	mpz_init(n);
	mpz_mul(n, p, q);
	mpz_t p_minus_1, q_minus_1, phi;
	mpz_init(p_minus_1);
    mpz_init(q_minus_1);
    mpz_init(phi);
	mpz_sub_ui(p_minus_1, p, 1);
	mpz_sub_ui(q_minus_1, q, 1);
	mpz_mul(phi, p_minus_1, q_minus_1);
	mpz_invert(d, e, phi);		
}

void RSA::decrypt(mpz_t rot, mpz_t c){
	mpz_powm(rot, c, d, n);
}

void RSA::exportPrivKey(){
	std::cout << "p = " << p << std::endl;
	std::cout << "q = " << q << std::endl;
	std::cout << "e = " << e << std::endl;
	std::cout << "d = " << d << std::endl;
	std::cout << "n = " << n << std::endl; 
}

void RSA::encryptPub(mpz_t rot, mpz_t m){
	encrypt(rot, m, e, n);
}

void encrypt(mpz_t rot, mpz_t m, mpz_t n, mpz_t e){
	mpz_powm(rot, m, e, n);
}
