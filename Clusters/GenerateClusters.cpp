#include "GenerateClusters.h"

namespace clusters {
std::pair<PointSet, std::vector<PointVector>> GenerateClusters() {
  int n, m, l; // n-количество необязательных точек;
               // m-количество обязательных точек;
               // l-размер квадрата [0,l]*[0,l], в котором распределны точки

  std::cout << "\nEnter count of optional points (n), count disk center for "
               "mandatory clusters"
               "points (m), size of square (l):\n";
  std::cin >> n >> m >> l;

  assert(std::cin.good());

  auto [pointSet, centerSet] = GeneratePointsInSquare(n, m, l);

  auto [optional, mandatory] = coveredPoints(pointSet, centerSet);

  return {optional, mandatory};
}

std::pair<PointSet, PointSet> GeneratePointsInSquare(int n, int m, int l) {

  PointSet pointSet = randomPoints::GenerateRandomPoints(
      n, l); //генерация точек, которые требуется покрыть
  PointSet centerSet =
      randomPoints::GenerateRandomPoints(m, l); //генерация центров

  return {pointSet, centerSet};
}

std::pair<PointSet, std::vector<PointVector>>
coveredPoints(PointSet pointSet, PointSet centerSet) {

  std::size_t m = centerSet.size();
  std::vector<PointVector> mandatory_(m);
  PointSet optional;

  std::size_t i = 0;
  for (auto center : centerSet) {
    for (auto point = pointSet.begin(); point != pointSet.end();) {
      if (center.Dist(*point) <= 1.0) {
        mandatory_[i].push_back(*point);
        point = pointSet.erase(point);
      } else
        point++;
    }
    if (!mandatory_[i].empty())++i;
  }
  auto beg = mandatory_.begin();
  std::vector<PointVector>::iterator end;
  if(i<m){
     end = static_cast<std::vector<PointVector>::iterator>(&mandatory_[i]);
    }
    else end =mandatory_.end();

  std::vector<PointVector> mandatory(beg, end);

  optional = pointSet;

  return {optional, mandatory};
}

std::vector<PointVector> Position(const PointSet &optional,
                                  const std::vector<PointVector> &CH) {
  int m = CH.size();
  std::vector<PointVector> Pi(m);
  
  PointVector IntersectionPoints;

  for (auto pt1 : optional) {
    for (auto pt2 : optional) {
      if (pt1 != pt2) {
        PointSet set_center;
        set_center = Disk(pt1).IntersectionDisk(pt2);
        if (!set_center.empty()) {
          for (auto center : set_center)
            IntersectionPoints.push_back(center);
        }
      };
    }
  }

  for (int i = 0; i < CH.size(); ++i) {
    if (CH[i].size() > 2) {
      Polygon plg{CH[i]};
      for (auto pt : IntersectionPoints) {
        if (plg.IsBelongPolygon(pt))
          Pi[i].push_back(pt);
      }
    }
    if (CH[i].size() == 1) {
      auto pt1 = CH[i][0];
      for (auto pt : IntersectionPoints) {
        if (Disk(pt1).PointIsBelong(pt))
          Pi[i].push_back(pt);
      }
    }
    if (CH[i].size() == 2) {
      auto pt1 = CH[i][0];
      auto pt2 = CH[i][1];
      for (auto pt : IntersectionPoints) {
        if (Disk(pt1).Dist(pt)<=1.0 && Disk(pt2).Dist(pt)<=1.0)
          Pi[i].push_back(pt);
      }
    }
  }

  return Pi;
};

} // namespace clusters