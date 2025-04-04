
#include "GeometryObjectsClass.h"

int main() {
  Point p1{2, 1};
  Point p2{2, 5};
  Point p3{7, 1};
  // Point p4{2,4};
  std::vector<Point> pt{p1, p2, p3};
  Polygon plg{pt};

  std::cout << plg.IsBelongPolygon({5, 2}) << std::endl;
  std::cout << plg.IsBelongPolygon({2, 1}) << std::endl;
  std::cout << plg.IsBelongPolygon({0, 0}) << std::endl;
  std::cout << plg.IsBelongPolygon({2, 3}) << std::endl;
  std::cout << plg.IsBelongPolygon({6, 1}) << std::endl;
  std::cout << plg.IsBelongPolygon({8, 1}) << std::endl;
  return 0;
}