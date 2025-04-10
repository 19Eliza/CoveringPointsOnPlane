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
    if (!mandatory_[i].empty())
      ++i;
  }
  auto beg = mandatory_.begin();
  std::vector<PointVector>::iterator end;
  if (i < m) {
    end = static_cast<std::vector<PointVector>::iterator>(&mandatory_[i]);
  } else
    end = mandatory_.end();

  std::vector<PointVector> mandatory(beg, end);

  optional = pointSet;

  return {optional, mandatory};
}

bool PointIsBelongIntersectionDisks(const Point &pt,
                                    const PointVector &pt_vec) {
  bool ind = true;
  for (auto pt_ : pt_vec) {
    if (pt.Dist(pt_) > 1.0) {
      ind = false;
      break;
    }
  }
  return ind;
}

PointSet DiskIntersectionDisks(const Point &pt, const PointVector &pt_vec) {

  PointSet BoundaryIntersection;

  for (auto iter_pt = pt_vec.begin(), end_iter_pt = pt_vec.end();
       iter_pt != end_iter_pt; ++iter_pt) {
    PointSet set_center;
    set_center = Disk(pt).IntersectionDisk(*iter_pt);

    if (!set_center.empty()) {
      for (auto center : set_center)
        if (PointIsBelongIntersectionDisks(center, pt_vec))
          BoundaryIntersection.insert(center);
    }
  }

  return BoundaryIntersection;
}

std::vector<PointVector> Position(const PointSet &optional,
                                  const std::vector<PointVector> &convexHull_) {
  int m = convexHull_.size();

  std::vector<PointVector> Pi(m);
  std::map<Point, std::map<Point, PointSet,cmp>,cmp> IntersectionPoints;

  for (auto iter_pt = optional.begin(), end_eter_pt = optional.end();
       iter_pt != end_eter_pt; ++iter_pt) {
    for (auto iter2_pt = optional.begin(); iter2_pt != end_eter_pt;
         ++iter2_pt) {
      if(*iter_pt!=*iter2_pt){

      PointSet set_center;
      set_center = Disk(*iter_pt).IntersectionDisk(*iter2_pt);
      if (!set_center.empty()) IntersectionPoints[*iter_pt].insert({*iter2_pt, set_center});
      
      }
    }
  }

  std::map<Point, bool,cmp> indicateIntersection;

  for (int i = 0; i < m; ++i) {

    if (!convexHull_[i].empty()) {

      for (auto iter_pt = IntersectionPoints.begin(),
                end_iter_pt = IntersectionPoints.end();
           iter_pt != end_iter_pt; ++iter_pt) {

        std::map<Point, PointSet,cmp> A = iter_pt->second;

        for (auto iter2_pt = A.begin(), iter2_pt_end = A.end();
             iter2_pt != iter2_pt_end; ++iter2_pt) {

          int ind = 0;
          for (auto center : iter2_pt->second)
            if (PointIsBelongIntersectionDisks(center, convexHull_[i])) {
              Pi[i].push_back(center);
              indicateIntersection[iter_pt->first] = true;
              ++ind;
            }

          if (ind == 0)
            indicateIntersection[iter_pt->first] = false;
        }
      }

      for (auto pt : optional) {
        if (indicateIntersection.find(pt) != indicateIntersection.end()) {

          if (!indicateIntersection[pt]) {

            auto BoundaryIntersection =
                DiskIntersectionDisks(pt, convexHull_[i]);
            if (!BoundaryIntersection.empty()) {
              for (auto pt1 : BoundaryIntersection)
                Pi[i].push_back(pt1);
            }
          }

        } else {
          auto BoundaryIntersection = DiskIntersectionDisks(pt, convexHull_[i]);
          if (!BoundaryIntersection.empty()) {
            for (auto pt1 : BoundaryIntersection)
              Pi[i].push_back(pt1);
          }
        }
      }

    }
    
    std::sort(Pi[i].begin(), Pi[i].end()); // сортировка
    auto last = std::unique(Pi[i].begin(), Pi[i].end()); // удаление дубликатов
    Pi[i].erase(last, Pi[i].end()); // обрезка

  }
    
  std::cout<<"End!\n";
  return Pi;
};

}// namespace clusters