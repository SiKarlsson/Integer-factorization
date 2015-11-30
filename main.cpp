#include <iostream>
#include <sstream>
#include <string>
#include <vector>

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

int main() {

    std::vector<int> numbers = readNumbers();

    writeNumbers(numbers);

    return 0;
}
