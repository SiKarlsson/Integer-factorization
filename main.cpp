
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

bool millerRabin(ttmath::UInt<bits> p,int iteration) {
	
	if (p < 2) {
        	return false;
    	}
   
	if (p != 2 && p % 2==0) {
        	return false;
	}
	
	ttmath::UInt<bits> s = p - 1;
    
	while (s % 2 == 0) {
        	s /= 2;
    	}
    
	for (int i = 0; i < iteration; i++) {
		ttmath::UInt<bits> a = randUInt() % (p - 1) + 1, temp = s;
        	//ttmath::UInt<bits> mod = modulo(a, temp, p);
        	ttmath::UInt<bits> mod = mod_exp(a, temp, p);
		
		while (temp != p - 1 && mod != 1 && mod != p - 1) {
			mod = mod_exp(mod, 2, p);
        		temp *= 2;
        	}
        
		if (mod != p - 1 && temp % 2 == 0) {
			return false;
		}
 	}
	return true;
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

bool isPrimeNaive(ttmath::UInt<bits> n) {
	if(n < 2) return false;
	if(n == 2) return true;
   	if(n % 2 == 0) return false;
    	for(ttmath::UInt<bits> i=3; (i*i)<=n; i+=2){
        	if(n % i == 0 ) return false;
   	 }
    	return true;
}

bool trivial(ttmath::UInt<bits> factor, ttmath::UInt<bits> N) {
	if(factor == 1 || factor == -1 ||factor==N||factor==N-N-N) {
		return true;
	}else{
		return false;	
	}
}

ttmath::UInt<bits> trial(ttmath::UInt<bits> N) {
	for(ttmath::UInt<bits> i = 2; i <= (N/2); i++) {
		if (N % i == 0) {
			return i;
		}
	}
	return -1;
}

ttmath::UInt<bits> g(ttmath::UInt<bits>	x, ttmath::UInt<bits> N) {
	return (x * x + 1) % N;
}

ttmath::UInt<bits> polles(ttmath::UInt<bits> N) {
	ttmath::UInt<bits> x = randUInt();
	ttmath::UInt<bits> y = x;
	ttmath::UInt<bits> d = 1;
	ttmath::UInt<bits> tmp;

	if (millerRabin(N, 5)) {
		//std::cout << N << " is a prime " << std::endl;
		return -1;
	}

	if (N < 1000) {
		//std::cout << N << " < 1000" << std::endl;
		return trial(N);
	}

	while(d == 1) {
		x = g(x, N);
		y = g(g(y, N), N);
		d = gcd(std::max(x, y) - std::min(x, y), N);
	}
	if (d == N) {
		if (! millerRabin(d, 5)) {
			//std::cout << d << " == " << N << std::endl;
			return trial(N);
		}
		return -1;
	} else {
		//std::cout << "found d: " << d << std::endl;
		if (millerRabin(d, 5) == false) {
			//std::cout << d << " is not a factor!" << std::endl;
			return trial(d);
		}
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
			factor = polles(N);
			//factor = pollardsRho(N);
			//std::cout << "factor for N = " << N << " -> " << factor << std::endl;
			if (factor == -1) {
				//std::cout << "map["<<N<<"] is cur "<< map[N] << std::endl;
				map[N]++;
				//std::cout << "map["<<N<<"] is now "<< map[N] << std::endl;
				//std::cout << N << " should be added to map" << std::endl;
				break;
			}

			//std::cout << "map["<<factor<<"] is cur "<< map[factor] << std::endl;
			map[factor]++;
			//std::cout << "map["<<factor<<"] is now "<< map[factor] << std::endl;
			N = N / factor;
			//std::cout << "new N = " << N << std::endl;
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
