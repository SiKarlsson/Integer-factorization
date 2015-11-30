#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <math.h>

/* Types */
typedef unsigned long mp_limb_t;
typedef long mp_size_t;
typedef unsigned long mp_bitcnt_t;
typedef mp_limb_t *mp_ptr;
typedef const mp_limb_t *mp_srcptr;
typedef struct {
  int _mp_alloc;
  int _mp_size;
  mp_limb_t *_mp_d;
} __mpz_struct;
typedef __mpz_struct mpz_t[1];

void mpz_init (mpz_t r) {
  static const mp_limb_t dummy_limb = 0xc1a0;
  r->_mp_alloc = 0;
  r->_mp_size = 0;
  r->_mp_d = (mp_ptr) &dummy_limb;
}

std::vector<std::string> readNumbers() {

    std::vector<std::string> numbers;
    std::string number;
    bool reading = true;

    while (reading) {
        std::cin >> number;

        if (number != "0") {
            numbers.push_back(number);
        } else {
            reading = false;
        }
    }

    return numbers;
}

void writeNumbers(std::vector<std::string> numbers) {

    for (std::string i : numbers) {
        std::cout << i << std::endl;
    }
}

int gcd(int a, int b) {

    int t;

    while (b != 0) {
        t = b;
        b = a % b;
        a = t;
    }

    return a;

    /*
    int d = 0;

    while ((a % 2 == 0) && (b % 2 == 0)) {
        a = a / 2;
        b = b / 2;
        d = d + 1;
    }

    while (a != b) {
        if (a % 2 == 0) {
            a = a / 2;
        } else if (b % 2 == 0) {
            b = b / 2;
        } else if (a > b) {
            a = (a - b)/2;
        } else {
            b = (b - a)/2;
        }
    }

    int g = a;

    return g * pow(2, d);
    */
}

int main() {

    //std::vector<std::string> numbers = readNumbers();

    //pollardsRho()

    // writeNumbers(numbers);

    std::cout << gcd(88, 32) << std::endl;

    return 0;
}
