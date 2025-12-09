#include <cstdint>
#include <fstream>
#include <iostream>
#include <print>
#include <sstream>
#include <stdexcept>
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

std::vector<std::string> transposeInput() {
  std::ifstream is("../input/day06.txt");
  std::vector<std::string> lines;
  std::string line;

  while (std::getline(is, line)) {
    lines.push_back(line);
  }

  lines.pop_back();

  std::vector<std::string> transposedLines(lines[0].size(), "");

  for (size_t row = 0; row < lines.size(); row++) {
    for (size_t col = 0; col < lines[0].size(); col++) {
      transposedLines[col] += lines[row][col];
    }
  }

  return transposedLines;
}

ul silver(const Equation &input) {
  ul total = 0;

  for (size_t i = 0; i < input.first[0].size(); i++) {
    ul lineTotal = input.second[i] == '*' ? 1 : 0;

    for (size_t j = 0; j < input.first.size(); j++) {
      if (input.second[i] == '*') {
        lineTotal *= input.first[j][i];
      } else if (input.second[i] == '+') {
        lineTotal += input.first[j][i];
      }
    }

    total += lineTotal;
  }

  return total;
}

ul gold(const std::vector<char> &operators) {
  auto input = transposeInput();
  ul total = 0;
  size_t operatorIndex = 0;
  ul lineTotal = operators[operatorIndex] == '*' ? 1 : 0;

  for (const auto &s : input) {
    try {
      if (operators[operatorIndex] == '*') {
        lineTotal *= std::stoul(s);
      } else if (operators[operatorIndex] == '+') {
        lineTotal += std::stoul(s);
      }
    } catch (const std::exception &) {
      total += lineTotal;
      operatorIndex++;
      lineTotal = operators[operatorIndex] == '*' ? 1 : 0;
    }
  }

  return total + lineTotal;
}

int main() {
  auto input = readInput();

  std::println("Silver {}", silver(input));
  std::println("Gold {}", gold(input.second));
}
