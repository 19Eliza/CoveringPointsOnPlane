#include "ConvexHall.h"

namespace convexHull {


bool LeftRotation(Point p1, Point p2, Point p3) {

  double u_x = p2.SetX() - p1.SetX();
  double u_y = p2.SetY() - p1.SetY();
  double v_x = p3.SetX() - p2.SetX();
  double v_y = p3.SetX() - p3.SetX();

  if (u_x * v_y - u_y * v_x >= 0) {
    return true;
  } else {
    return false;
  }
}

std::vector<Point> ConvexHull(std::vector<Point> &p) {

  sort(p.begin(), p.end(),cmp());
  std::vector<Point> L_upper;

  if(p.size()==1){
    L_upper.push_back(p[0]);
    return L_upper;
  }

  int n = p.size();

  L_upper.push_back(p[0]);
  L_upper.push_back(p[1]);

  int j = 1;

  for (int i = 2; i < n; i++) {
    L_upper.push_back(p[i]);

    while (L_upper.size() > 2 &&
           LeftRotation(*(L_upper.end() - 3), *(L_upper.end() - 2),
                         *(L_upper.end() - 1))) {
      L_upper.erase(L_upper.end() - 2);
    }
  }

  std::vector<Point> L_lower;

  L_lower.push_back(p[n - 1]);
  L_lower.push_back(p[n - 2]);

  for (int i = n - 3; i > -1; i--) {
    L_lower.push_back(p[i]);

    while (L_lower.size() > 2 &&
           LeftRotation(*(L_lower.end() - 3), *(L_lower.end() - 2),
                         *(L_lower.end() - 1))) {
      L_lower.erase(L_lower.end() - 2);
    }
  }

  L_lower.pop_back();
  L_lower.erase(L_lower.begin());

  L_upper.insert(L_upper.end(), L_lower.begin(), L_lower.end());

  return L_upper;
}
} // namespace convex_hull
