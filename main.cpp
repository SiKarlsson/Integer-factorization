
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

bool isPrimeNaive(ttmath::UInt<bits> n) {
	if(n < 2) return false;
	if(n == 2) return true;
   	if(n % 2 == 0) return false;
    	for(ttmath::UInt<bits> i=3; (i*i)<=n; i+=2){
        	if(n % i == 0 ) return false;
   	 }
    	return true;
}

bool isPrime(ttmath::UInt<bits> n, int k) {
	
	return isPrimeNaive(n);

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
		std::cout << "9" << std::endl;
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
	if(factor == 1 || factor == -1 ||factor==N||factor==N-N-N) {
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
	
	for(unsigned int j = 0; j < bits; j++) {
		srand(time(NULL));
		x0.table[j] = rand();
	}

	x0 = x0 % N;
	y0 = x0;

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
		tmp = gcd(std::max(x1, y1) - std::min(x1, y1), N);

		if (tmp == N) {
			b++;
			continue;
		}	
	
		if(!trivial(tmp, N) && isPrime(tmp, 5)) {
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

	std::map<ttmath::UInt<bits>, ttmath::UInt<bits>> map;

	while(true) {

		std::cin >> N;

		if(N == 0) {
			break;
		}	
		
		while (N != 1) {
			factor = pollardsRho(N);
			map[factor]++;
			N = N / factor;
		}		

		for(auto const &it : map) {
			s = s + it.first.ToString() + "^" + it.second.ToString() + " ";
		}
		factors.push_back(s);
		s = "";
		
		for(auto const &it : map) {
                      map[it.second] = 0;
                }

		map.clear(); 

	}
	
	for(int i = 0; i < factors.size(); i++) {
		std::cout << factors[i] << std::endl;
	}
	

	return 0;
}
