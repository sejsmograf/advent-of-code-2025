#include <cstdint>
#include <functional>
#include <iostream>
#include <fstream>
#include <numeric>
#include <print>
#include <sstream>
#include <string>
#include <vector>

using ul = uint64_t;
using Column = std::vector<ul>;
using Operators = std::vector<char>;
using Equation = std::pair<std::vector<Column>, Operators>;

Equation readInput() {

  Equation equation;

  std::ifstream is("../input/day06.txt");
  std::string line;

  std::getline(is, line);
  std::stringstream ss(line);
  size_t numberIndex;
  ul number;

  while (ss >> number) {
    equation.first.push_back({number});
  }

  while (std::getline(is, line)) {
    ss = std::stringstream(line);
    if (line[0] == '*' || line[0] == '+') {
      break;
    }

    size_t index = 0;

    while (ss >> number) {
      equation.first[index].push_back(number);
      index++;
    }
  }

  char op;
  while (ss >> op) {
    equation.second.push_back(op);
  }

  // for (int i = 0; i < equation.first[0].size(); i++) {
  //   std::println("columns {}", equation.first[i].size());
  // }

  return equation;
};

ul silver(const Equation &input) {
  ul total = 0;

  for (size_t i = 0; i < input.first.size(); i++) {
    char op = input.second[i];

    if (op == '*') {
      total += std::accumulate(input.first[i].begin(), input.first[i].end(), 1,
                               std::multiplies<ul>());
    } else if (op == '+') {
      total += std::accumulate(input.first[i].begin(), input.first[i].end(), 0);
    }
  }

  return total;
}

int main() {
  auto input = readInput();

  std::println("\nSilver {}", silver(input));

  // printEquation(input);
  // for (auto dupa : input.first[1]) {
  //   std::println("{}", dupa);
  // }
}
