#include <iostream>
#include <sstream>
#include <string>
#include <vector>

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

int main() {

    std::vector<std::string> numbers = readNumbers();

    //pollardsRho()

    writeNumbers(numbers);

    return 0;
}
