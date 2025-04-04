#include "GeometryObjectsClass.h"
#include "RandomPoints.h"
#include "ConvexHall.h"
#include "GenerateClusters.h"
#include <iostream>

int main() {

  auto [optional, mandatory] = clusters::GenerateClusters();//Set of optional points, vector of PointVec of mandatory points
  std::cout << "Count of optional set points: " << optional.size() << std::endl;

  auto m = mandatory.size();
  // std::cout << "m: " << m<< std::endl;

  std::vector<PointVector> ConvexHullMandatoryPoint(m);
  int j = 0;
  for (auto i = 0; i < m; i++) {
    if (!mandatory[i].empty()) {
      ConvexHullMandatoryPoint.at(i) = convexHull::ConvexHull(mandatory[i]);
      j++;
    }
  }
  std::cout << "Clusters count of mandatory points: " << m << std::endl;

  std::vector<PointVector> I=clusters::Position(optional,ConvexHullMandatoryPoint);
  
  return 0;
}