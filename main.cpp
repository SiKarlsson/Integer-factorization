
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <math.h>
#include <map>

const int bits = 4;

ttmath::UInt<bits> randUInt() {
	ttmath::UInt<bits> n;
	for (unsigned int i = 0; i < bits; i++) {
		srand(time(NULL));
		n.table[i] = rand();	
	}
	return n;
}


ttmath::UInt<bits> gcd(ttmath::UInt<bits> a, ttmath::UInt<bits> b) {
	ttmath::UInt<bits> t;
	while(b != 0) {
		t = b;
		b = a % b;
		a = t;	
	}

	return a;
}

bool isPrime(ttmath::UInt<bits> n, int k) {
	ttmath::UInt<bits> x, a, d, r, tmp;

	if(n % 2 == 0) {
		return false;
	}
	if(n < 7) {
		return true;
	}

	d = n-1;
	r = 0;

	while(d % 2 == 0) {
		d = d / 2;
		r++;
	}

	for(int i = 0; i < k; i++) {
		a = randUInt();
        	a = a % (n-4) + 2;
		
		tmp = a;
		tmp.Pow(d);
		x = tmp % n;
		if (x == 1 || x == n-1) {
			continue;
		}
		for (ttmath::UInt<bits> j = 0; j < (r - 1); j++) {
			x.Pow(2);
			x = x % n;
			if (x == 1) {
				return false;
			}
			if (x == n-1) {
				continue;
			}
		}
		return false;	
	}
	return true;
}

bool trivial(ttmath::UInt<bits> factor, ttmath::UInt<bits> N) {
	if(factor==1||factor==-1) {
		return true;
	}else{
		return false;	
	}
}


ttmath::UInt<bits> pollardsRho(ttmath::UInt<bits> N) {
	ttmath::UInt<bits> x0, x1, tmp, y0, y1, b;

	if (isPrime(N, 10)) {
		return N;
	}
	else {
		std::cout << N << " is not a prime!" << std::endl;
	}
	
	for(unsigned int j = 0; j < bits; j++) {
		srand(time(NULL));
		x0.table[j] = rand();
	}

	x0 = x0 % N;
	y0 = x0;

	std::cout << "x0: " << x0 << std::endl;

	b = 1;

	while(true) {
		tmp = x0;
		tmp.Pow(2);
		x1 = (tmp + b) % N;
		tmp = y0;
		tmp.Pow(2);
		y1 = (tmp + b);
		y1.Pow(2);
		y1 = (y1 + b) % N;
		std::cout << "x1: " << x1 << std::endl;
		std::cout << "y1: " << y1 << std::endl;
		tmp = gcd(std::max(x1, y1) - std::min(x1, y1), N);
		std::cout << "tmp: " << tmp << std::endl;

		if (tmp == N) {
			b++;
			continue;
		}
		if(!trivial(tmp, N)) {
			return tmp;
		}		

		x0 = x1;
		y0 = y1;
	}
}

int main() {
	ttmath::UInt<bits> N, factor;
	
	std::string s;
	std::vector<std::string> factors;

	while(true) {
		std::map<ttmath::UInt<bits>, ttmath::UInt<bits>> map;	
		std::cin >> N;

		if(N == 0) {
			break;
		}	
		do {
			std::cout << "N: " << N << std::endl;
       			//std::cout << "Factoring: " << N << std::endl;
        		factor = pollardsRho(N);
        		//std::cout << factor << std::endl;
			while(N % factor == 0) {
				N = N / factor;
				map[factor]++;
			}
			std::cout << "factor: " << factor << std::endl;
		} while (N != 1);
		for(auto const &it : map) {
			s = s + it.first.ToString() + "^" + it.second.ToString() + " ";
		}
		factors.push_back(s);
		s = "";
	}
	
	for(int i = 0; i < factors.size(); i++) {
		std::cout << factors[i] << std::endl;
	}

	return 0;
}
