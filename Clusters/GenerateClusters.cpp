#include "GenerateClusters.h"

namespace clusters {


  #include <iostream>
  #include <tuple>
  #include <limits>
  
  std::tuple<int, int, int> EnterParameters() {
      int totalPointsNumber = 0;
      int countClusters = 0;
      int sizeSquare = 0;
  
      while (true) {
          std::cout << "\nSeparated by a space enter total number of points, clusters count, size of square:\n";
          std::cin >> totalPointsNumber >> countClusters >> sizeSquare;
  
          if (std::cin.fail() || sizeSquare <= 1) {
              std::cin.clear(); 
              std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
              std::cout << "Invalid input! Make sure to enter 3 numbers separated by a space and that size of square > 1.\n";
          } else {
              break; 
          }
      }
  
      return std::make_tuple(totalPointsNumber, countClusters, sizeSquare);
  }
  

std::pair<PointSet, std::vector<PointVector>> GenerateClusters(int n, int m, int l) {

  auto [pointSet, centerSet] = GeneratePointsInSquare(n, m, l);

  auto [optional, mandatory] = coveredPoints(pointSet, centerSet);

  return {optional, mandatory};
}

std::pair<PointSet, PointSet> GeneratePointsInSquare(int n, int m, int l) {

  PointSet centerSet = randomPoints::GenerateRandomPointsAtOneDistance(m, l); //генерация центров

  PointSet pointSet = randomPoints::GenerateRandomPoints(n-m, l); //генерация точек, которые требуется покрыть
 
  return {pointSet, centerSet};
}

std::pair<PointSet, std::vector<PointVector>>
coveredPoints(PointSet pointSet, PointSet centerSet) {

  std::size_t m = centerSet.size();

  std::vector<PointVector> mandatoryAll(m);

  PointSet optional;

  std::size_t i = 0;

  for (auto center : centerSet) {
    for (auto point = pointSet.begin(); point != pointSet.end();) {
      if (center.Dist(*point) <= 1.0) {
        mandatoryAll[i].push_back(*point);
        point = pointSet.erase(point);
      } else
        point++;
    }
    ++i;
  }

  std::vector<PointVector> mandatory(m);

  optional = pointSet;

  for(int i=0;i<m;++i){
    if(!mandatoryAll[i].empty()){
      auto [resultMandatoryCluster,RemainingPoints]=ChooseRandomCountPoints(mandatoryAll[i]);
      mandatory[i]=resultMandatoryCluster;
      for(auto pt:RemainingPoints)optional.insert(pt);
    }
  }

  auto iter=centerSet.begin();
  for(int i=0;i<mandatory.size() && iter!=centerSet.end();++iter,++i)
    mandatory[i].push_back(*iter);

  return {optional, mandatory};
}

std::pair<PointVector,PointVector> ChooseRandomCountPoints(PointVector mandatoryCluster){

  auto countAllPoints=mandatoryCluster.size();
  auto Q=countAllPoints*0.8;
  std::random_device rd;  
  std::mt19937 gen(rd()); 
  std::uniform_int_distribution<> distrib(0, Q); 

  int q = distrib(gen);

  std::shuffle(mandatoryCluster.begin(), mandatoryCluster.end(), gen);

  PointVector resultMandatoryCluster;
  for (int i = 0; i < q; ++i)
      resultMandatoryCluster.push_back(mandatoryCluster[i]);

  PointVector RemainingPoints;
  for (int i = q; i < countAllPoints; ++i)
      RemainingPoints.push_back(mandatoryCluster[i]);
  
  return {resultMandatoryCluster,RemainingPoints};
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
    
    std::sort(Pi[i].begin(), Pi[i].end()); 
    auto last = std::unique(Pi[i].begin(), Pi[i].end()); 
    Pi[i].erase(last, Pi[i].end());

  }
    
  //std::cout<<"End!\n";
  return Pi;
};

}// namespace clusters