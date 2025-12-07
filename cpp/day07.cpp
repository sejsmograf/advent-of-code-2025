#include <fstream>
#include <map>
#include <print>
#include <string>
#include <unordered_set>
#include <vector>

std::vector<std::string> readInput() {
  std::vector<std::string> input;

  std::ifstream is("../input/bigboy.txt");
  std::string line;

  while (std::getline(is, line)) {
    input.emplace_back(line);
  }

  return input;
};

std::pair<size_t, size_t> findStart(const std::vector<std::string> &input) {
  for (size_t row = 0; row < input.size(); row++) {
    for (size_t col = 0; col < input.size(); col++) {
      if (input[row][col] == 'S') {
        return {row, col};
      }
    }
  }

  return {-1, -1};
}

int silver(const std::vector<std::string> &input) {
  int total = 0;

  auto startPos = findStart(input);
  std::unordered_set<size_t> previousBeamPos = {startPos.second};
  std::unordered_set<size_t> newBeamPos;

  for (size_t row = startPos.first + 1; row < input.size(); row++) {
    for (auto pos : previousBeamPos) {
      if (input[row][pos] == '^') {
        total++;
        if (pos - 1 >= 0) {
          newBeamPos.insert(pos - 1);
        }
        if (pos + 1 < input[0].size()) {
          newBeamPos.insert(pos + 1);
        }
      } else {
        newBeamPos.insert(pos);
      }
    }

    previousBeamPos = newBeamPos;
    newBeamPos.clear();
  }

  return total;
}

using ul = unsigned long long;

ul gold(const std::vector<std::string> &input, size_t rowIndex, size_t beamPos,
        std::map<std::pair<size_t, size_t>, ul> &memo) {
  if (rowIndex == input.size())
    return 1;
  std::pair<size_t, size_t> pos = {rowIndex, beamPos};
  if (memo.contains(pos)) {
    return memo[pos];
  }

  const std::string &row = input[rowIndex];

  ul combined = 0;
  if (row[beamPos] == '^') {
    if (beamPos - 1 >= 0) {
      ul leftRecursion = gold(input, rowIndex + 1, beamPos - 1, memo);
      combined += leftRecursion;
    }
    if (beamPos + 1 < row.length()) {
      ul rightRecursion = gold(input, rowIndex + 1, beamPos + 1, memo);
      combined += rightRecursion;
    }

    memo.insert({pos, combined});
    return combined;
  } else {
    ul downward = gold(input, rowIndex + 1, beamPos, memo);
    memo.insert({pos, downward});
    return downward;
  }
}

int main() {
  auto input = readInput();

  auto startPos = findStart(input);

  std::println("Silver {}", silver(input));
  std::map<std::pair<size_t, size_t>, ul> memo;
  std::println("Gold {}", gold(input, 0, startPos.second, memo));
}
