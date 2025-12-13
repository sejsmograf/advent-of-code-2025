#include <algorithm>
#include <climits>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iterator>
#include <print>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

int numberFromLights(const std::string &lights) {
  int total = 0;
  for (size_t i = 0; i < lights.size(); i++) {
    if (lights[i] == '#') {
      total += pow(2, lights.size() - i - 1);
    }
  }

  return total;
}

int numberFromLightsGold(const std::vector<int> &lights) {
  int total = 0;
  for (size_t i = 0; i < lights.size(); i++) {
    total += lights[i] * pow(2, lights.size() - i - 1);
  }

  return total;
}

std::vector<std::pair<int, std::vector<int>>> readInput(bool gold = false) {
  std::vector<std::pair<int, std::vector<int>>> input;

  std::ifstream is("../input/day10.txt");
  std::string line;

  size_t lineIndex = 0;
  while (std::getline(is, line)) {
    size_t end = line.find(']');
    std::string lights = line.substr(1, end - 1);
    std::stringstream ss(line.substr(end + 1));
    size_t maxPower = lights.size();
    int target = numberFromLights(lights);
    input.push_back({target, {}});

    char sep;
    int num;

    do {
      ss >> sep;
    } while (isspace(sep));

    while (sep != '{') {
      ss >> sep;
      int total = 0;
      while (sep != ')') {
        if (sep == ',') {
          ss >> sep;
          continue;
        }

        ss.putback(sep);
        ss >> num;
        total += pow(2, maxPower - num - 1);
        ss >> sep;
      }
      input[lineIndex].second.push_back(total);
      ss >> sep;
      while (isspace(sep))
        ss >> sep;
    }

    if (gold) {
      std::vector<int> lights;
      while (sep != '}') {
        int num;
        ss >> num;
        ss >> sep;
        lights.push_back(num);
      }

      auto number = numberFromLightsGold(lights);
      input[lineIndex].first = number;
    }

    lineIndex++;
  }

  return input;
};

int recurseOptimalButtons(int target, const std::vector<int> &buttons,
                          int &best, size_t index = 0, int count = 0) {
  if (target == 0)
    return count;

  if (count >= best)
    return best;

  int result = -1;

  for (size_t i = index; i < buttons.size(); i++) {
    int resPush = recurseOptimalButtons(target ^ buttons[i], buttons, best,
                                        i + 1, count + 1);
    if (resPush != -1) {
      best = std::min(best, resPush);
      if (result == -1 || resPush < result)
        result = resPush;
    }

    int resSkip = recurseOptimalButtons(target, buttons, best, i + 1, count);
    if (resSkip != -1) {
      best = std::min(best, resSkip);
      if (result == -1 || resSkip < result)
        result = resSkip;
    }
  }

  return result;
}

int recurseOptimalButtonsGold(int target, const std::vector<int> &buttons,
                          int &best, size_t index = 0, int count = 0) {
  if (target == 0)
    return count;

  if (count >= best)
    return best;

  int result = -1;

  for (size_t i = index; i < buttons.size(); i++) {
    int resPush = recurseOptimalButtons(target ^ buttons[i], buttons, best,
                                        i + 1, count + 1);
    if (resPush != -1) {
      best = std::min(best, resPush);
      if (result == -1 || resPush < result)
        result = resPush;
    }

    int resSkip = recurseOptimalButtons(target, buttons, best, i + 1, count);
    if (resSkip != -1) {
      best = std::min(best, resSkip);
      if (result == -1 || resSkip < result)
        result = resSkip;
    }
  }

  return result;
}


int silver(const std::vector<std::pair<int, std::vector<int>>> &input) {
  int total = 0;

  for (size_t i = 0; i < input.size(); i++) {
    auto line = input[i];
    auto buttons = line.second;
    std::vector<int> filteredButtons;
    std::copy_if(buttons.begin(), buttons.end(),
                 std::back_inserter(filteredButtons),
                 [line](int a) { return (line.first & a) != 0; });

    int best = INT_MAX;
    auto min = recurseOptimalButtons(line.first, line.second, best);

    total += min;
  }

  return total;
}

int gold(const std::vector<std::pair<int, std::vector<int>>> &input) {
  int total = 0;

  for (size_t i = 0; i < input.size(); i++) {
    auto line = input[i];
    auto buttons = line.second;
    std::sort(buttons.begin(), buttons.end(), [](auto a, auto b) {
      return a > b;
    });

    int best = INT_MAX;
    auto min = recurseOptimalButtonsGold(line.first, line.second, best);

    total += min;
  }

  return total;
}

int main() {
  auto inputGold = readInput(true);
  std::println("Gold {}", gold(inputGold));
  // std::println("{}", silver(input));
}
