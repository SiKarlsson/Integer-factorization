#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <math.h>

std::vector<int> readNumbers() {

    std::vector<int> numbers;
    int number;
    bool reading = true;

    while (reading) {
        std::cin >> number;

        if (number != 0) {
            numbers.push_back(number);
        } else {
            reading = false;
        }
    }

    return numbers;
}

void writeNumbers(std::vector<int> numbers) {

    for (int i : numbers) {
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
