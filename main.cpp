
#include <sstream>
#include <string>
#include <vector>
#include <math.h>
#include <map>

const int bits = 4;

/**
 * Returns a random UInt
 */
ttmath::UInt<bits> randUInt() {
	ttmath::UInt<bits> n;
	for (unsigned int i = 0; i < bits; i++) {
		srand(time(NULL));
		n.table[i] = rand();	
	}
	return n;
}

/**
 * Calculates base^exponent * mod N
 */
ttmath::UInt<bits> mod_exp(ttmath::UInt<bits> base, ttmath::UInt<bits> exponent, ttmath::UInt<bits> N) {
	if (N == 1) {
		return 0;
	}
	ttmath::UInt<bits> res = 1;
	base = base % N;
	while (exponent > 0) {
		if (exponent % 2 == 1) {
			res = (res*base) % N;
		}
		exponent = exponent >> 1;
		base = (base * base) % N;
	}
	return res;
}

/**
 * Determine if a number is prime using the Miller-Rabin method
 */
bool millerRabin(ttmath::UInt<bits> n, int k) {
	
	if (n < 2) {
        	return false;
	}
   
	if (n != 2 && n % 2==0) {
        	return false;
	}
	
	ttmath::UInt<bits> r = n - 1;
    
	while (r % 2 == 0) {
        	r = r/2;
    	}
    
	for (int i = 0; i < k; i++) {
		ttmath::UInt<bits> a = randUInt() % (n - 1) + 1, temp = r;
        	ttmath::UInt<bits> mod = mod_exp(a, temp, n);
		
		while (temp != n - 1 && mod != 1 && mod != n - 1) {
			mod = mod_exp(mod, 2, n);
        		temp *= 2;
        	}
        
		if (mod != n - 1 && temp % 2 == 0) {
			return false;
		}
 	}
	return true;
}

/**
 * Return the greatest common divisor of two numbers
 */
ttmath::UInt<bits> gcd(ttmath::UInt<bits> a, ttmath::UInt<bits> b) {
	ttmath::UInt<bits> t;
	while(b != 0) {
		t = b;
		b = a % b;
		a = t;	
	}

	return a;
}

/**
 * The g-function used for the Pollard's rho algorithm
 */
ttmath::UInt<bits> g(ttmath::UInt<bits>	x, ttmath::UInt<bits> N) {
	return (x * x + 1) % N;
}

/**
 * An implementation of the Pollard's rho algorithm for finding
 * prime factors of composite numbers
 */
ttmath::UInt<bits> pollardsRho(ttmath::UInt<bits> N) {
	ttmath::UInt<bits> x = randUInt();
	ttmath::UInt<bits> y = x;
	ttmath::UInt<bits> d = 1;
	ttmath::UInt<bits> tmp;

	if (millerRabin(N, 5)) {
		return -1;
	}

	while(d == 1) {
		x = g(x, N);
		y = g(g(y, N), N);
		d = gcd(std::max(x, y) - std::min(x, y), N);
	}
	if (d == N) {
		return -1;
	} else {
		return d;
	}
}

int main() {

	ttmath::UInt<bits> N, factor;
	
	std::string s;
	std::vector<std::string> factors;

	std::map<ttmath::UInt<bits>, ttmath::UInt<bits>> map;

	while(true) {
		factor = 1;

		std::cin >> N;

		if(N == 0) {
			break;
		}	
		
		while (factor != -1) {
			factor = pollardsRho(N);
			if (factor == -1) {
				map[N]++;
				break;
			}

			map[factor]++;
			N = N / factor;
		}		
		
		int test = 1;
		for(auto const &it : map) {
			s = s + it.first.ToString() + "^" + it.second.ToString();
			map[it.first] = 0;
			if (test < map.size()) {
				s = s + " ";
			}
			test++;
		}
		factors.push_back(s);
		s = "";
		
		map.clear();
	}
	
	for(int i = 0; i < factors.size(); i++) {
		std::cout << factors[i] << std::endl;
	}

	return 0;
}
