#include <cmath>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <print>


using Ranges = std::vector<std::pair<unsigned long long, unsigned long>>;

Ranges readInput() {
	Ranges pairs;
	std::ifstream is("../input/day02.txt");
	std::string line;
	std::getline(is, line); 
	std::stringstream ss(line);

	unsigned long long firstNumber;
	unsigned long long secondNumber;
	char separator;
	while(ss >> firstNumber) {
		ss >> separator;
		ss >> secondNumber;
		ss >> separator;
		pairs.push_back({firstNumber, secondNumber});
	}

	return pairs;
};

size_t digitCount(unsigned long long number) {
	return (size_t) log10(number) + 1;
}


std::vector<int> findDivisors(int number) {
	std::vector<int> divisors;

	for(int i = 1; i <= sqrt(number); i++) {
		if(number % i == 0) {
			divisors.push_back(i);
			if(i != number/i && i != 1) {
				divisors.push_back(number / i);
			}
		}
	}

	return divisors;
}

bool isIdInvalid(unsigned long long number) {
	size_t length = digitCount(number);
	if(length % 2 != 0) {
		return false;
	}

	unsigned long long divisor = pow(10, length / 2);

	unsigned long long left = number / divisor;
	unsigned long long right = number % divisor;

	return left == right;
}

bool isIdInvalidGold(unsigned long long number) {
	size_t length = digitCount(number);
	if(length < 2) {
		return false;
	}
	auto divisors = findDivisors(length);

	for (auto div: divisors) {
		size_t step = pow(10, div);
		unsigned long long copied = number;
		bool valid = true;

		while(digitCount(copied) > div) {
			unsigned long long previous = copied % step;
			copied /= step;
			unsigned long long current = copied % step;

			if (current != previous) {
				valid = false;
				break;
			}
		}

		if(valid) {
			return true;
		}
	}
	return false;
}



unsigned long long solve(const Ranges& input, bool (*predicate)(unsigned long long)) {
	unsigned long long invalidIdsSummedUp = 0;
	for(auto range: input) {
		for(long i = range.first; i <= range.second; i++) {
			if(predicate(i)){ 
				invalidIdsSummedUp += i;
			}
		}
	}
	return invalidIdsSummedUp;
}



int main() {
	auto input = readInput();

	std::println("Silver: {}", solve(input, &isIdInvalid));
	std::println("Gold: {}", solve(input, &isIdInvalidGold));
} 
