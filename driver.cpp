#include <iostream>
#include <unistd.h>
#include <cstring>
#include "rsa.h"

int main(int argc, char** argv){

	if(argc < 2){
	usage:
		std::cout << "Usage: " << argv[0] << " [-p p -q q | {-b b}] -m m | -h" << std::endl;
		return 0;
	}

	char *p = (char*)"null";
	char *q = (char*)"null";
	mpz_t m;
	int bitlength=1024;
	mpz_init(m);
	mpz_set_ui(m, -1);
	
	RSA *rsa = nullptr;
	
	char opt;
	while((opt = getopt(argc, argv, "p:q:m:b:h")) != -1){
		switch(opt){
		case 'p':
			p = optarg;
			break;
		case 'q':
			q = optarg;
			break;
		case 'b':
			bitlength = std::atoi(optarg);
			break;
		case 'm':
			mpz_set_str(m, optarg, 10);
			break;
		case 'h':
			goto usage;
			break;
		}
	}

	if(mpz_cmp_si(m, -1)==0){
		std::cout << "Error: -m not set" << std::endl;
		goto usage;
	}
	if(strcmp(p, "null")==0 && strcmp(q, "null")==0){
		rsa = new RSA(bitlength);
	}

	
	if(strcmp(p, "null")!=0 || strcmp(q, "null")!=0){
		if(strcmp(p, "null")==0){
			std::cout << "Error: -p not set" << std::endl;
			goto usage;
		}
		if(strcmp(q, "null")==0){
			std::cout << "Error: -q not set" << std::endl;
			goto usage;
		}
		rsa = new RSA(p, q);
	}


	rsa->exportPrivKey();
	
	mpz_t c;
	mpz_init(c);
	encrypt(c, m, rsa->getPubN(), rsa->getPubE());

	std::cout << std::hex << std::showbase;
	std::cout << "Encrypting " << m << " as " << c << std::endl;
	mpz_t plaintext;
	mpz_init(plaintext);
	rsa->decrypt(plaintext, c);
	std::cout << "Decrypting " << c << " as " << m << std::endl;

	delete rsa;
	
	return 0;
}
