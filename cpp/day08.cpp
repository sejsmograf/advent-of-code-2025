#include <algorithm>
#include <cmath>
#include <fstream>
#include <print>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

using l = unsigned long long;
using Point = std::tuple<l, l, l>;
using PointPair = std::pair<Point, Point>;

std::vector<Point> readInput() {
  std::vector<Point> input;

  std::ifstream is("../input/day08.txt");
  std::string line;

  while (std::getline(is, line)) {
    std::stringstream ss(line);
    l coordX;
    l coordY;
    l coordZ;
    char sep;

    ss >> coordX;
    ss >> sep;
    ss >> coordY;
    ss >> sep;
    ss >> coordZ;
    input.push_back({coordX, coordY, coordZ});
  }

  return input;
};

double euclideanDistance(Point point1, Point point2) {
    double dx = (double)std::get<0>(point1) - (double)std::get<0>(point2);
    double dy = (double)std::get<1>(point1) - (double)std::get<1>(point2);
    double dz = (double)std::get<2>(point1) - (double)std::get<2>(point2);

    return std::sqrt(dx*dx + dy*dy + dz*dz);
}

std::vector<std::pair<PointPair, double>>
findClosestPairs(const std::vector<Point> &input) {
  using Entry = std::pair<PointPair, double>;

  std::set<PointPair> inserted;
  std::vector<std::pair<PointPair, double>> pairsWithDistance;

  auto cmp = [](Entry a, Entry b) { return a.second < b.second; };
  std::priority_queue<Entry, std::vector<Entry>, decltype(cmp)> heap;

  for (auto point1 : input) {
    for (const auto point2 : input) {
      if (point1 == point2 || inserted.contains({point2, point1}))
        continue;

      pairsWithDistance.push_back({{point1, point2}, euclideanDistance(point1, point2)});
      inserted.insert({point1, point2});
    }
  }

  std::sort(pairsWithDistance.begin(), pairsWithDistance.end(),
            [](auto a, auto b) { return a.second < b.second; });

  return pairsWithDistance;
}

l silver(const std::vector<std::pair<PointPair, double>>& closestPairs, size_t n) {
  std::vector<std::set<Point>> circuits;

  for (size_t i = 0; i < n; i++) {
    auto [point1, point2] = closestPairs[i].first;

    auto containingFirst =
        std::find_if(circuits.begin(), circuits.end(),
                     [point1](auto c) { return c.contains(point1); });

    auto containingSecond =
        std::find_if(circuits.begin(), circuits.end(),
                     [point2](auto c) { return c.contains(point2); });

    if (containingFirst == circuits.end() &&
        containingSecond == circuits.end()) {
      circuits.push_back({point1, point2});
    } else if (containingFirst == containingSecond) {
      continue;
    } else if (containingFirst != circuits.end() &&
               containingSecond != circuits.end()) {
      if (containingFirst < containingSecond) {
        containingFirst->insert(containingSecond->begin(),
                                containingSecond->end());
        circuits.erase(containingSecond);
      } else {
        containingSecond->insert(containingFirst->begin(),
                                 containingFirst->end());
        circuits.erase(containingFirst);
      }
    } else if (containingFirst != circuits.end()) {
      containingFirst->insert(point2);
    } else if (containingSecond != circuits.end()) {
      containingSecond->insert(point1);
    }
  }


  std::sort(circuits.begin(), circuits.end(), [](auto a, auto b) {
    return a.size() > b.size();
  });

  return circuits[0].size() * circuits[1].size() * circuits[2].size();
}


l gold(const std::vector<std::pair<PointPair, double>>& closestPairs, size_t n) {
  std::vector<std::set<Point>> circuits;

  size_t index = 0;
  Point point1, point2;
  while (circuits.size() != 1 || circuits[0].size() != n) {
    point1 = closestPairs[index].first.first;
    point2 = closestPairs[index].first.second;
    double dist = closestPairs[index].second;
    index++;


    auto containingFirst =
        std::find_if(circuits.begin(), circuits.end(),
                     [point1](auto c) { return c.contains(point1); });

    auto containingSecond =
        std::find_if(circuits.begin(), circuits.end(),
                     [point2](auto c) { return c.contains(point2); });

    if (containingFirst == circuits.end() &&
        containingSecond == circuits.end()) {
      circuits.push_back({point1, point2});
    } else if (containingFirst == containingSecond) {
      continue;
    } else if (containingFirst != circuits.end() &&
               containingSecond != circuits.end()) {
      if (containingFirst < containingSecond) {
        containingFirst->insert(containingSecond->begin(),
                                containingSecond->end());
        circuits.erase(containingSecond);
      } else {
        containingSecond->insert(containingFirst->begin(),
                                 containingFirst->end());
        circuits.erase(containingFirst);
      }
    } else if (containingFirst != circuits.end()) {
      containingFirst->insert(point2);
    } else if (containingSecond != circuits.end()) {
      containingSecond->insert(point1);
    }
  }


  return std::get<0>(point1) * std::get<0>(point2);
}

int main() {
  auto input = readInput();
  auto closestPairs = findClosestPairs(input);

  std::println("Silver {}", silver(closestPairs, 10));
  std::println("Gold {}", gold(closestPairs, input.size()));
}
