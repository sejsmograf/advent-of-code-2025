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
using Row = std::vector<ul>;
using Operators = std::vector<char>;
using Equation = std::pair<std::vector<Row>, Operators>;

Equation readInput() {
  Equation equation;

  std::ifstream is("../input/day06.txt");
  std::string line;
  std::stringstream ss(line);

  while (std::getline(is, line)) {
    Row row;
    ul number;
    ss = std::stringstream(line);

    if (line[0] == '*' || line[0] == '+') {
      break;
    }

    while (ss >> number) {
      row.push_back(number);
    }

    equation.first.push_back(row);
  }

  char op;
  while (ss >> op) {
    equation.second.push_back(op);
  }

  return equation;
};

ul silver(const Equation &input) {
  ul total = 0;

  for (size_t i = 0; i < input.first[0].size(); i++) {
    ul lineTotal = input.second[i] == '*' ? 1: 0;

    for (size_t j = 0; j < input.first.size(); j++) {
      if(input.second[i] == '*') {
        lineTotal *= input.first[j][i];
      }
      else if(input.second[i] == '+') {
        lineTotal += input.first[j][i];
      }
    }

    total +=lineTotal;
  }

  return total;
}

int main() {
  auto input = readInput();

  for (int i =0 ; i < 4; i++) {
    std::println("\n");
    for (auto d: input.first[i]) {
      std::println("{}", d);
    }
  }


  std::println("\nSilver {}", silver(input));


}
