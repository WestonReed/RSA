#include <iostream>
#include <unistd.h>
#include "rsa.h"

int main(int argc, char** argv){

	if(argc < 2){
	usage:
		std::cout << "Usage: " << argv[0] << " [-p p -q q -e e | -g] -m m | -h" << std::endl;
		return 0;
	}
	
	long long p=-1, q=-1;
	int e=-1, m=-1;

	RSA *rsa = nullptr;
	
	char opt;
	while((opt = getopt(argc, argv, "p:q:e:m:gh")) != -1){
		switch(opt){
		case 'p':
			p = std::atoll(optarg);
			break;
		case 'q':
			q = std::atoll(optarg);
			break;
		case 'e':
			e = std::atoi(optarg);
			break;
		case 'm':
			m = std::atoi(optarg);
			break;
		case 'g':
			rsa = new RSA();
			break;
		case 'h':
			goto usage;
			break;
		}
	}

	if(m == -1){
		std::cout << "Error: -m not set" << std::endl;
		goto usage;
	}
	if(p == -1 && q == -1 && e == -1 && !rsa){
		std::cout << "Error: You must provide a p, q, and e, or generate a key with the -g flag" << std::endl;
		goto usage;
	}

	
	if(p != -1 || q != -1 || e != -1){
		if(p == -1){
			std::cout << "Error: -p not set" << std::endl;
			goto usage;
		}
		if(q == -1){
			std::cout << "Error: -q not set" << std::endl;
			goto usage;
		}
		if(e == -1){
			std::cout << "Error: -e not set" << std::endl;
			goto usage;
		}
		rsa = new RSA(p, q, e);
	}


	rsa->exportPrivKey();
	
	int c = encrypt(m, rsa->getPubN(), rsa->getPubE());

	std::cout << std::hex << std::showbase;
	std::cout << "Encrypting " << m << " as " << c << std::endl;
	std::cout << "Decrypting " << c << " as " << rsa->decrypt(c) << std::endl;

	delete rsa;
	
	return 0;
}
