#include <fstream>
#include <string>
#include <vector>
#include <print>



std::vector<std::string> readInput() {
	std::vector<std::string> lines;
	std::ifstream is("../input/bigboy.txt");
	std::string line;

	while(std::getline(is, line)) {
		lines.push_back(line);
	}

	return lines;
};



int solve(std::vector<std::string>& input, bool recurse, int sum) {
	std::vector<std::vector<int>> neighbourMap(input.size(), std::vector<int>(input[0].size(), 0));

	const std::array<std::pair<int, int>, 8> neighbours = {{
	 {1, 0}, {1, 1}, {1, -1}, {-1, 0}, {-1, 1}, {-1, -1}, {0, 1}, {0, -1}
	}};

	for(size_t row = 0; row < input.size(); row++) {
		for(size_t col = 0; col < input[0].size(); col++) {
			if(input[row][col] == '@') {
				for (auto coord : neighbours) {
					int newRow = row - coord.first;
					int newCol = col - coord.second;

					if(newRow < 0 || newRow >= input.size() || newCol < 0 || newCol >= input[0].size()) {
						continue;
					}
					neighbourMap[newRow][newCol]++;
				}
			}
		}
	}

	int total = 0;
	for(size_t row = 0; row < input.size(); row++) {
		for(size_t col = 0; col < input[0].size(); col++) {
			if(neighbourMap[row][col] < 4 && input[row][col] == '@') {
				total++;
				if(recurse) {
					input[row][col] = '.';
				}
			}
		}
	}

	if(!recurse || total == 0) return sum+total;;
	return solve(input, true, sum+total);
}



int main() {
	auto input = readInput();

	std::println("Silver: {}", solve(input, false, 0));
	std::println("Gold: {}", solve(input, true, 0));
} 
