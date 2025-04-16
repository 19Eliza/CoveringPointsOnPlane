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



std::set<Point, cmp> GenerateRandomPointsAtOneDistance(int n, int l) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis(0.0, l);

  std::set<Point, cmp> pointSet;

  int N = n ;

  auto checkOneDistance = [](const PointSet& ptSet, const Point& pt) -> bool {
    return std::all_of(ptSet.begin(), ptSet.end(),
        [pt](const Point& pt1) {
            return pt1.Dist(pt) > 0.5;
        }
    );
  };

  int iterLimit=10000;
  int iter=0;
  while (pointSet.size() != N) {
    Point pt{dis(gen), dis(gen)};
    ++iter;
    if(checkOneDistance(pointSet,pt) || iter>=iterLimit){
      pointSet.insert(pt);
      iter=0;
    }
  }

  return pointSet;
}

} // namespace randomPoints