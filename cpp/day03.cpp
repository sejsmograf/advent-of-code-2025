#include <fstream>
#include <string>
#include <vector>
#include <print>


using ul = unsigned long;

std::vector<std::string> readInput() {
	std::vector<std::string> lines;
	std::ifstream is("../input/day03.txt");
	std::string line;

	while(std::getline(is, line)) {
		lines.push_back(line);
	}

	return lines;
};



ul solve(const std::vector<std::string>& input, ul digitNumber) {
	ul total = 0;

	for (const auto& line: input) {
		size_t previousMaxIndex = -1;
		ul lineTotal = 0;

		for (size_t digit = 1; digit <= digitNumber; digit++) {
			char max = 0;

			for (size_t i = previousMaxIndex + 1; i < line.length() - digitNumber + digit; i++) {
				if(line[i] > max) {
					max = line[i];
					previousMaxIndex = i;
				}
			}
			lineTotal += (max - '0') * pow(10, digitNumber - digit);

		}
		total += lineTotal;
	}


	return total;
}



int main() {
	auto input = readInput();

	std::println("Silver: {}", solve(input, 2));
	std::println("Gold: {}", solve(input, 12));
} 
