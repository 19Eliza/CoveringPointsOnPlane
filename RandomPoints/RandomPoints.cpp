#include "RandomPoints.h"

namespace randomPoints {
std::set<Point, cmp> GenerateRandomPoints(int n, int l) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis(0.0, l);

  std::set<Point, cmp> pointSet;

  int N = n ;

  while (pointSet.size() != N) {
    pointSet.insert({dis(gen), dis(gen)});
  }

  return pointSet;
}
} // namespace randomPoints