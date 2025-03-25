#include "GenerateClusters.h"

namespace clusters {
std::pair<PointSet, std::vector<PointVector>> GenerateClusters() {
  int n, m, l; // n-количество необязательных точек;
               // m-количество обязательных точек;
               // l-размер квадрата [0,l]*[0,l], в котором распределны точки

  std::cout << "\nEnter count of optional points (n), count of mandatory "
               "points (m), size of square (l):\n";
  std::cin >> n >> m >> l;

  assert(std::cin.good());

  auto [pointSet, centerSet] = GeneratePointsInSquare(n, m, l);

  auto [optional, mandatory] = coveredPoints(pointSet, centerSet);

  return {optional, mandatory};
}

std::pair<PointSet, PointSet> GeneratePointsInSquare(int n, int m, int l) {

  std::set<Point, cmp> pointSet = randomPoints::GenerateRandomPoints(n, l); //генерация точек, которые требуется покрыть
  std::set<Point, cmp> centerSet =
      randomPoints::GenerateRandomPoints(m, l); //генерация центров

  return {pointSet, centerSet};
}

std::pair<PointSet, std::vector<PointVector>>
coveredPoints(PointSet pointSet, PointSet centerSet) {

  std::vector<PointVector> mandatory(centerSet.size());
  PointSet optional;

  std::size_t i = 0;
  for (auto center : centerSet) {
    for (auto point = pointSet.begin(); point != pointSet.end();) {
      if (center.Dist(*point) <= 1.0) {
        mandatory[i].push_back(*point);
        point = pointSet.erase(point);
      } else
        point++;
    }
    ++i;
  }

  optional = pointSet;

  return {optional, mandatory};
}

} // namespace clusters