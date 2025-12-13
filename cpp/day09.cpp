#include <algorithm>
#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <print>
#include <sstream>
#include <string>
#include <vector>

using Point = std::pair<int, int>;
using l = int64_t;

std::vector<Point> readInput() {
  std::vector<Point> input;

  std::ifstream is("../input/day09.txt");
  std::string line;

  while (std::getline(is, line)) {
    std::stringstream ss(line);
    int coordX;
    int coordY;
    char sep;

    ss >> coordX;
    ss >> sep;
    ss >> coordY;
    input.push_back({coordX, coordY});
  }

  return input;
};

l rectArea(Point point1, Point point2) {
  return (static_cast<l>(abs(point1.first - point2.first)) + 1) *
         (static_cast<l>(abs(point1.second - point2.second)) + 1);
}

l silver(const std::vector<Point> &input) {
  l maxArea = 0;

  for (auto p1 : input) {
    for (auto p2 : input) {
      auto area = rectArea(p1, p2);
      if (area > maxArea) {
        maxArea = area;
      }
    }
  }

  return maxArea;
}

l gold(const std::vector<Point> &input) {
  std::vector<std::pair<Point, Point>> verticalWalls;
  std::vector<std::pair<Point, Point>> horizontalWalls;

  for (size_t i = 0; i < input.size(); i++) {
    auto nextIndex = i == (input.size() - 1) ? 0 : i + 1;

    auto curr = input[i];
    auto next = input[nextIndex];

    bool isVerticalWall = curr.first == next.first;
    if (isVerticalWall) {
      verticalWalls.push_back({curr, next});
    } else {
      horizontalWalls.push_back({curr, next});
    }
  }

  std::sort(verticalWalls.begin(), verticalWalls.end(),
            [](auto a, auto b) { return a.first < b.first; });

  l maxArea = 0;
  for (const auto p1 : input) {
    for (const auto p2 : input) {
      auto area = rectArea(p1, p2);
      if (area < maxArea) {
        continue;
      }

      auto leftX = std::min(p1.first, p2.first);
      auto rightX = std::max(p1.first, p2.first);
      auto topY = std::min(p1.second, p2.second);
      auto bottomY = std::max(p1.second, p2.second);

      bool verticalWallInside =
          std::find_if(
              verticalWalls.begin(), verticalWalls.end(),
              [leftX, rightX, topY, bottomY](auto wall) {
                auto wallTop = std::min(wall.first.second, wall.second.second);
                auto wallBottom =
                    std::max(wall.first.second, wall.second.second);

                return wall.first.first > leftX && wall.first.first < rightX &&
                       std::max(topY, wallTop) < std::min(bottomY, wallBottom);
              }) != verticalWalls.end();

      if (verticalWallInside)
        continue;

      bool horizontalWallInside =
          std::find_if(
              horizontalWalls.begin(), horizontalWalls.end(),
              [leftX, rightX, topY, bottomY](auto wall) {
                auto wallLeft = std::min(wall.first.first, wall.second.first);
                auto wallRight = std::max(wall.first.first, wall.second.first);

                return wall.first.second > topY &&
                       wall.first.second < bottomY &&
                       std::max(leftX, wallLeft) < std::min(rightX, wallRight);
              }) != horizontalWalls.end();

      if (horizontalWallInside)
        continue;

      if (area > maxArea) {
        maxArea = area;
      }
    }
  }
  return maxArea;
}

int main() {
  auto input = readInput();

  std::println("Silver {}", silver(input));
  std::println("Gold {}", gold(input));
}
