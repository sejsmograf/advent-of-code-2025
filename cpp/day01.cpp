#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <print>


const int STARTING_ROTATION = 50;
enum class Direction {
	LEFT,
	RIGHT,
};

using Rotations = std::vector<std::pair<Direction, int>>;

Rotations readInput() {
	Rotations rotations;
	std::ifstream is("../input/day01.txt");
	std::string line;

	while(std::getline(is, line)) {
		std::stringstream ss(line);
		char direction;
		ss >> direction;
		int rotation;
		ss >> rotation;
		rotations.push_back({ direction == 'L' ? Direction::LEFT : Direction::RIGHT, rotation});
	}

	return rotations;
};

int silver(const Rotations& input) {
	int rotationDegree = STARTING_ROTATION;
	int zeroedCount = 0;
	for(const auto rotation: input) {
		if(rotation.first == Direction::LEFT) {
			rotationDegree -= rotation.second;
		}
		else {
			rotationDegree += rotation.second;
		}

		if(rotationDegree % 100 == 0) {
			zeroedCount++;
		}
	}
	return zeroedCount;
}

int gold(const Rotations& input) {
	int rotationDegree = STARTING_ROTATION;
	int zeroedCount = 0;
	for(const auto rotation: input) {
		for (int i = 0; i < rotation.second; i++) {
			if(rotation.first == Direction::LEFT) {
				rotationDegree--;
			}
			else {
				rotationDegree++;
			}
			if(rotationDegree % 100 == 0) {
				zeroedCount++;
			}
		}
	}

	return zeroedCount;
}

int main() {
	auto input = readInput();
	std::println("Silver: {}", silver(input));
	std::println("Gold: {}", gold(input));
} 
