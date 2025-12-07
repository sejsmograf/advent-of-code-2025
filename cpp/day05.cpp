#include <algorithm>
#include <fstream>
#include <cstdint>
#include <print>
#include <sstream>
#include <string>
#include <vector>

using ul = uint64_t;
using IngredientRanges = std::vector<std::pair<ul, ul>>;
using Ingredients = std::vector<ul>;

std::pair<IngredientRanges, Ingredients> readInput() {
  IngredientRanges ranges;
  Ingredients ingredients;

  std::ifstream  is("../input/day05.txt");
  std::string line;

  while(std::getline(is, line)) {
    if(line.empty()) break;
    std::stringstream ss(line);

    char sep;
    ul start;
    ul end;
    ss >> start;
    ss >> sep;
    ss >> end;
    ranges.push_back({ start, end });
  }

  while(std::getline(is, line)) {
    std::stringstream ss(line);
    ul ingredient;
    ss >> ingredient;
    ingredients.push_back(ingredient);
  }

  return { ranges, ingredients };
};



IngredientRanges concatenateRanges(const IngredientRanges& ranges) {
  auto copy = ranges;

  std::sort(copy.begin(), copy.end(), [](std::pair<ul, ul> a, std::pair<ul, ul> b) {
    return a.first < b.first;
  });

  IngredientRanges concatenated = { copy[0] };

  for(size_t i = 1; i < copy.size(); i++) {
    auto firstRange = concatenated[concatenated.size() - 1];
    auto secondRange = copy[i];

    if(firstRange.second >= secondRange.first) {
      concatenated[concatenated.size() - 1].second = std::max(firstRange.second, secondRange.second);
    }
    else {
      concatenated.push_back(secondRange);
    }
  }

  return concatenated;
}



ul silver(const std::pair<IngredientRanges, Ingredients>& input) {
  ul total = 0;

  auto concatenated = concatenateRanges(input.first);
  for(auto ingredient: input.second) {
    for(auto pair: concatenated) {
      if(ingredient >= pair.first && ingredient <= pair.second) {
        total++;
        break;
      }
    }
  }

  return total;
}

ul gold(const IngredientRanges& ingredients) {
  ul total = 0;
  auto concatenated = concatenateRanges(ingredients);

  for(const auto pair: concatenated) {
    total += pair.second - pair.first + 1;
  }

  return total;
}



int main() {
  auto input = readInput();
  auto concat = concatenateRanges(input.first);

  for (const auto pair: concat) {
    std::println("Range {}", pair);
  }

  std::println("\nSilver {}", silver(input));
  std::println("Gold {}", gold(input.first));
} 
